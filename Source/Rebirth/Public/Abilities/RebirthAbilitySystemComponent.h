// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rebirth.h"
#include "AbilitySystemComponent.h"
#include "RebirthAbilitySystemComponent.generated.h"

class URebirthGameplayAbility;

UCLASS()
class REBIRTH_API URebirthAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	URebirthAbilitySystemComponent();

	void GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<URebirthGameplayAbility*>& ActiveAbilities);

	static URebirthAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);
};
