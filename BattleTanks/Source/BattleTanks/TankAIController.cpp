// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* MyTank = GetControlledTank();

	if (MyTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank %s reporting in."), *(MyTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No possessed tank."));
	}

	ATank* PlayerTank = GetPlayerTank();

	if (PlayerTank != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI tank %s found player tank %s."), *(MyTank->GetName()), *(PlayerTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find player's tank."));
	}

	return;
}



ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (PlayerPawn != nullptr)
	{
		return Cast<ATank>(PlayerPawn);
	}
	
	return nullptr;
}


