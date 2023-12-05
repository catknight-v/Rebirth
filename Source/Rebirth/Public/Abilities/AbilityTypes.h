// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rebirth.h"
#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "AbilityTypes.generated.h"

class UGameplayEffect;
class UTargetType;

USTRUCT(BluePrintType)
struct REBIRTH_API FGameplayEffectContainer
{
	GENERATED_BODY()

public:
	FGameplayEffectContainer() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TSubclassOf<UTargetType> TargetType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TArray<TSubclassOf<UGameplayEffect>> TargetGameplayEffectClasses;
};

USTRUCT(BluePrintType)
struct REBIRTH_API FGameplayEffectContainerSpec
{
	GENERATED_BODY()

public:
	FGameplayEffectContainerSpec() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	FGameplayAbilityTargetDataHandle TargetData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;

	bool HasValidEffects() const;

	bool HasValidTargets() const;

	void AddTargets(const TArray<FHitResult>& HitResults, const TArray<AActor*>& TargetActors);
};