// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractionComponent.generated.h"

class ACapsuleActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REBIRTH_API UInteractionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	UFUNCTION(BlueprintCallable)
	void InteractWithInteractingActor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CapsuleActor)
	ACapsuleActor* CapsuleActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = InteractingActor)
	AActor* InteractingActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CapsuleShape)
	float CapsuleHalfHeight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CapsuleShape)
	float CapsuleRadius;
	
	//UFUNCTION(BlueprintCallable)
	//void EnterInteractableArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION(BlueprintCallable)
	//void LeaveInteractableArea(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//UFUNCTION(BlueprintCallable)
	//void InteractWith(AActor* Interactor);

	
};
