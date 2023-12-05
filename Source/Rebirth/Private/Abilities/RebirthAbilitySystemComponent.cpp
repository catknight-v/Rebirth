// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/RebirthAbilitySystemComponent.h"
#include "Abilities/RebirthGameplayAbility.h"
#include "AbilitySystemGlobals.h"

URebirthAbilitySystemComponent::URebirthAbilitySystemComponent(){}

void URebirthAbilitySystemComponent::GetActiveAbilitiesWithTags(const FGameplayTagContainer& GameplayTagContainer, TArray<URebirthGameplayAbility*>& ActiveAbilities)
{
	TArray<FGameplayAbilitySpec*> AbilitiesToActivate;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, AbilitiesToActivate, false);

	for (FGameplayAbilitySpec* Spec : AbilitiesToActivate)
	{
		TArray<UGameplayAbility*> AbilityInstances = Spec->GetAbilityInstances();
		for (UGameplayAbility* ActiveAbility : AbilityInstances)
		{
			ActiveAbilities.Add(Cast<URebirthGameplayAbility>(ActiveAbility));
		}
	}
}

URebirthAbilitySystemComponent* URebirthAbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent)
{
	return Cast<URebirthAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}
