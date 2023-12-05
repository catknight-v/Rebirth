// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/RebirthAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/PlayerController.h"
#include "Characters/RebirthCombatCharacterBase.h"

URebirthAttributeSet::URebirthAttributeSet()
	: Health(1.f)
	, MaxHealth(1.f)
	, Energy(0.f)
	, MaxEnergy(0.f)
	, Damage(0.f)
	, MoveSpeed(0.f)
{}

void URebirthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float DeltaValue = 0.f;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		DeltaValue = Data.EvaluatedData.Magnitude;
	}
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ARebirthCombatCharacterBase* TargetCharacter = nullptr;

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ARebirthCombatCharacterBase>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		// once 修改了Damage值，表示AS即将受到的一次伤害结算
		// 此处同时处理Health与Damage

		AActor* SourceActor = nullptr;
		AController* SourceController = nullptr;
		ARebirthCombatCharacterBase* SourceCharacter = nullptr;
		//当伤害来源合法 继续计算
		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
			SourceController = Source->AbilityActorInfo->PlayerController.Get();
			if (SourceController == nullptr && SourceActor != nullptr)
			{
				if (APawn* Pawn = Cast<APawn>(SourceActor))
				{
					SourceController = Pawn->GetController();
				}
			}
			//再填充
			if (SourceController)
			{
				SourceCharacter = Cast<ARebirthCombatCharacterBase>(SourceController->GetPawn());
			}
			else
			{
				SourceCharacter = Cast<ARebirthCombatCharacterBase>(SourceActor);
			}

			if (Context.GetEffectCauser())
			{
				SourceActor = Context.GetEffectCauser();
			}

			FHitResult HitResult;
			if (Context.GetHitResult())
			{
				HitResult = *Context.GetHitResult();
			}
			//属性结算
			const float LocalDamageDone = GetDamage();
			SetDamage(0.f);
			const float OldHealth = GetHealth();
			SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));
			if (TargetCharacter)
			{
				//伤害与生命值结算继续转交给character
				TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);
				TargetCharacter->HandleHealthChanged(-LocalDamageDone, SourceTags);
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		//Health属性结算
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		if (TargetCharacter)
		{
			TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetEnergyAttribute())
	{
		//Energy属性结算
		SetEnergy(FMath::Clamp(GetEnergy(), 0.0f, GetMaxEnergy()));
		if (TargetCharacter)
		{
			TargetCharacter->HandleEnergyChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	{
		//MoveSpeed属性结算
		if (TargetCharacter)
		{
			TargetCharacter->HandleMoveSpeedChanged(DeltaValue, SourceTags);
		}
	}

}
