// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rebirth.h"
#include "Engine/AssetManager.h"
#include "RebirthAssetManager.generated.h"

class UItem;
class UGameplayLevelInfo;

UCLASS()
class REBIRTH_API URebirthAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	URebirthAssetManager() {}
	virtual void StartInitialLoading() override;

	static const FPrimaryAssetType WeaponItemType;
	static const FPrimaryAssetType OutfitItemType;
	static const FPrimaryAssetType ConsumableItemType;
	static const FPrimaryAssetType KeyItemType;
	static const FPrimaryAssetType InvisibleItemType;

	static const FPrimaryAssetType LevelInfoType;

	static URebirthAssetManager& Get();

	UItem* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
	
	UGameplayLevelInfo* ForceLoadLevelInfo(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
};
