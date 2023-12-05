// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Weapons/ActorResetInfo.h"
#include "MeleeWeaponActor.generated.h"

class UCapsuleComponent;

UCLASS()
class REBIRTH_API AMeleeWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeWeaponActor();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkeletalMesh)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = SkeletalMesh)
	FName MeshSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = CapsuleCollision)
	UCapsuleComponent* CapsuleCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EventStates)
	bool bAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EventStates)
	FGameplayTag AttackEventTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = EventStates)
	TSet<AActor*> AttackingActors;

	UFUNCTION(BlueprintCallable)
	virtual void BeginWeaponAttack(FGameplayTag EventTag);

	UFUNCTION(BlueprintCallable)
	virtual void EndWeaponAttack();

	UFUNCTION()
	virtual void ActorBeginOverlapped(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	virtual void ActorEndOverlapped(AActor* OverlappedActor, AActor* OtherActor);


};
