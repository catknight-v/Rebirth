// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/RebirthGameplayAbility.h"
#include "Abilities/TargetType.h"
#include "Characters/RebirthCombatCharacterBase.h"
#include "Abilities/RebirthAbilitySystemComponent.h"

URebirthGameplayAbility::URebirthGameplayAbility(){}

FGameplayEffectContainerSpec URebirthGameplayAbility::MakeEffectContainerSpecFromContainer(const FGameplayEffectContainer& Container, const FGameplayEventData& EventData)
{
	FGameplayEffectContainerSpec ReturnSpec;
	AActor* OwningActor = GetOwningActorFromActorInfo();
	ARebirthCombatCharacterBase* OwningCharacter = Cast<ARebirthCombatCharacterBase>(OwningActor);
	URebirthAbilitySystemComponent* OwningASC = URebirthAbilitySystemComponent::GetAbilitySystemComponentFromActor(OwningActor);
	if (OwningActor)
	{
		//如果TargetType合法
		if (Container.TargetType.Get())
		{
			TArray<FHitResult> HitResults;
			TArray<AActor*> TargetActors;
			const UTargetType* TargetTypeCDO = Container.TargetType.GetDefaultObject();
			AActor* AvatarActor = GetAvatarActorFromActorInfo();
			TargetTypeCDO->GetTargets(OwningCharacter, AvatarActor, EventData, HitResults, TargetActors);
			ReturnSpec.AddTargets(HitResults, TargetActors);
		}

		for (const TSubclassOf<UGameplayEffect>& EffectClass : Container.TargetGameplayEffectClasses)
		{
			ReturnSpec.TargetGameplayEffectSpecs.Add(MakeOutgoingGameplayEffectSpec(EffectClass));
		}
	}

	return ReturnSpec;
}

FGameplayEffectContainerSpec URebirthGameplayAbility::MakeEffectContainerSpec(FGameplayTag ContainerTag, const FGameplayEventData& EventData)
{
	FGameplayEffectContainer* FoundContainer = EffectContainerMap.Find(ContainerTag);

	if (FoundContainer)
	{
		return MakeEffectContainerSpecFromContainer(*FoundContainer, EventData);
	}
	return FGameplayEffectContainerSpec();
}

TArray<FActiveGameplayEffectHandle> URebirthGameplayAbility::ApplyEffectContainerSpec(const FGameplayEffectContainerSpec& ContainerSpec)
{
	TArray<FActiveGameplayEffectHandle> AllEffects;
	for (const FGameplayEffectSpecHandle& SpecHandle : ContainerSpec.TargetGameplayEffectSpecs)
	{
		//实际实施GE
		AllEffects.Append(K2_ApplyGameplayEffectSpecToTarget(SpecHandle, ContainerSpec.TargetData));
	}

	return AllEffects;
}

TArray<FActiveGameplayEffectHandle> URebirthGameplayAbility::ApplyEffectContainer(FGameplayTag ContainerTag, const FGameplayEventData& EventData)
{
	FGameplayEffectContainerSpec Spec = MakeEffectContainerSpec(ContainerTag, EventData);
	return ApplyEffectContainerSpec(Spec);
}
