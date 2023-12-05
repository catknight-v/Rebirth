// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Engine/Engine.h"
#include "Animation/AnimMontage.h"
#include "PlayMontageAndWaitForEvent.generated.h"

class URebirthAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlayMontageAndWaitForEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);
/**
 * 
 */
UCLASS()
class REBIRTH_API UPlayMontageAndWaitForEvent : public UAbilityTask
{
	GENERATED_BODY()

public:
	UPlayMontageAndWaitForEvent(const FObjectInitializer& ObjectInitializer);
	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual FString GetDebugString() const override;
	virtual void OnDestroy(bool AbilityEnded) override;

	UPROPERTY(BlueprintAssignable)
	FPlayMontageAndWaitForEventDelegate OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FPlayMontageAndWaitForEventDelegate OnBlendOut;

	UPROPERTY(BlueprintAssignable)
	FPlayMontageAndWaitForEventDelegate OnInterrupted;

	UPROPERTY(BlueprintAssignable)
	FPlayMontageAndWaitForEventDelegate OnCancelled;

	/** One of the triggering gameplay events happened */
	UPROPERTY(BlueprintAssignable)
	FPlayMontageAndWaitForEventDelegate EventReceived;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UPlayMontageAndWaitForEvent* PlayMontageAndWaitForEvent(
			UGameplayAbility* OwningAbility,
			FName TaskInstanceName,
			UAnimMontage* MontageToPlay,
			FGameplayTagContainer EventTags,
			float Rate = 1.f,
			FName StartSection = NAME_None,
			bool bStopWhenAbilityEnds = true,
			float AnimRootMotionTranslationScale = 1.f
		);

private:

	UPROPERTY()
	UAnimMontage* MontageToPlay;

	UPROPERTY()
	FGameplayTagContainer EventTags;

	UPROPERTY()
	float Rate;

	UPROPERTY()
	FName StartSection;

	UPROPERTY()
	float AnimRootMotionTranslationScale;

	UPROPERTY()
	bool bStopWhenAbilityEnds;

	bool StopPlayingMontage();

	URebirthAbilitySystemComponent* GetTargetASC();

	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);
	void OnAbilityCancelled();
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;
	FDelegateHandle CancelledHandle;
	FDelegateHandle EventHandle;
};
