// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rebirth.h"
#include "Items/ItemTypes.h"
#include "Characters/RebirthCombatCharacterBase.h"
#include "CombatCharacterDefaultInventory.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct REBIRTH_API FDefaultInventory
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DefaultInventories)
	TMap<FPrimaryAssetId, FItemData> Data;
};

UCLASS(Blueprintable)
class REBIRTH_API UCombatCharacterDefaultInventory : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DefaultInventories)
	TMap<TSubclassOf<ARebirthCombatCharacterBase>, FDefaultInventory> Data;

};
