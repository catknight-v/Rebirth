// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnActor.generated.h"


UCLASS()
class REBIRTH_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawn)
	TSubclassOf<APawn> PawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawn)
	TSubclassOf<AController> ControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawn)
	APawn* CurrentPawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Spawn)
	AController* CurrentController;
	
	UFUNCTION(BlueprintCallable, Category = Spawn)
	void Spawn();

protected:

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
};
