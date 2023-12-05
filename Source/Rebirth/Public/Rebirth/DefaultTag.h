// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DefaultTag.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class REBIRTH_API UDefaultTag : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tag)
	FGameplayTag AbilityInitTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tag)
	FGameplayTag AbilityJumpTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tag)
	FGameplayTag AbilityMeleeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tag)
	FGameplayTag AbilityDodgeTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tag)
	FGameplayTag PawnEnemyTag;

};
