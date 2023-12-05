// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rebirth.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "TargetType.generated.h"

class ARebirthCombatCharacterBase;
class AActor;
struct FGameplayEventData;

UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class REBIRTH_API UTargetType : public UObject
{
	GENERATED_BODY()

public:

	UTargetType(){}

	UFUNCTION(BlueprintNativeEvent)
	void GetTargets(ARebirthCombatCharacterBase* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;
};


UCLASS(NotBlueprintable)
class REBIRTH_API UTargetType_UseOwner :public UTargetType
{
	GENERATED_BODY()

public:
	UTargetType_UseOwner() {}

	virtual void GetTargets_Implementation(ARebirthCombatCharacterBase* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};

UCLASS(NotBlueprintable)
class REBIRTH_API UTargetType_UseEventData :public UTargetType
{
	GENERATED_BODY()

public:
	UTargetType_UseEventData() {}

	virtual void GetTargets_Implementation(ARebirthCombatCharacterBase* TargetingCharacter, AActor* TargetingActor, FGameplayEventData EventData, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const override;
};