// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/SpawnActor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void ASpawnActor::Spawn()
{
	UWorld* World = GetWorld();
	FTransform Transform;
	Transform.SetLocation(GetActorLocation());
	CurrentPawn = Cast<APawn>(World->SpawnActor(PawnClass.Get(), &Transform));
	CurrentController = Cast<AController>(World->SpawnActor(ControllerClass.Get(), &Transform));
	if (CurrentPawn)
	{
		CurrentPawn->SetOwner(this);
	}
	if (CurrentController)
	{
		CurrentController->SetOwner(this);
		CurrentController->Possess(CurrentPawn);
	}
}

void ASpawnActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CurrentController)
	{
		CurrentController->Destroy();
	}
	if (CurrentPawn)
	{
		CurrentPawn->Destroy();
	}
	Super::EndPlay(EndPlayReason);
}
