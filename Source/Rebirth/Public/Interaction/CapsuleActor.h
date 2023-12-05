// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CapsuleActor.generated.h"

class UCapsuleComponent;

UCLASS()
class REBIRTH_API ACapsuleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACapsuleActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = InteractingActor)
	AActor* InteractingActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = InteractingActor)
	UCapsuleComponent* CapsuleComponent;

	UFUNCTION(BlueprintCallable)
	void EnterInteractableArea(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void LeaveInteractableArea(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void InteractWith(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void InteractWithInteractingActor();


};
