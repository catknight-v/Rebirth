// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/Item.h"
#include "Rebirth/RebirthAssetManager.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class REBIRTH_API UWeaponItem : public UItem
{
	GENERATED_BODY()

public:
	UWeaponItem()
	{
		ItemType == URebirthAssetManager::WeaponItemType;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TSubclassOf<AActor> WeaponActor;
};
