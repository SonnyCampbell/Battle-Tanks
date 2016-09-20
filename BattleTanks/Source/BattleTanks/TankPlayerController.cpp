#include "BattleTanks.h"
#include "TankPlayerController.h"


ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* MyTank = GetControlledTank();

	if (MyTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlling %s."), *(MyTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No possessed tank."));
	}

	return;
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());;
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank() == nullptr) { return; }

	FVector HitLocation; // Out parameter	

	// Get world location of linetrace through crosshair
	bool HitSomething = GetSightRayHitLocation(HitLocation);

	// If it hits landscape
	if (HitSomething)
	{
		//		Tell controlled tank to aim at this point
		UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *HitLocation.ToString());
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{

	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);


	//Deproject the screen position of the crosshair to a world direction
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line trace along that direction and see what we hit

		///Set up query parameters
		FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

		FHitResult Hit;
		bool HitWorld = GetWorld()->LineTraceSingleByChannel(
			Hit,
			PlayerCameraManager->GetCameraLocation(),
			PlayerCameraManager->GetCameraLocation() + (LookDirection * LineTraceRange),
			ECollisionChannel::ECC_Visibility,
			TraceParameters
		);

		if (HitWorld)
		{
			HitLocation = Hit.Location;
			return HitWorld;
		}
		
	}
	
	return false;
	
}


bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation;

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}





