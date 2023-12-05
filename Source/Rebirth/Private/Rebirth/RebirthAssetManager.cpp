// Fill out your copyright notice in the Description page of Project Settings.


#include "Rebirth/RebirthAssetManager.h"
#include "Items/Item.h"
#include "Gameplay/GameplayLevelInfo.h"
#include "AbilitySystemGlobals.h"

const FPrimaryAssetType URebirthAssetManager::WeaponItemType = TEXT("WeaponItem");
const FPrimaryAssetType URebirthAssetManager::OutfitItemType = TEXT("OutfitItem");
const FPrimaryAssetType URebirthAssetManager::ConsumableItemType = TEXT("ConsumableItem");
const FPrimaryAssetType URebirthAssetManager::KeyItemType = TEXT("KeyItem");
const FPrimaryAssetType URebirthAssetManager::InvisibleItemType = TEXT("InvisibleItem");

const FPrimaryAssetType URebirthAssetManager::LevelInfoType = TEXT("LevelInfo");

void URebirthAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
}

URebirthAssetManager& URebirthAssetManager::Get()
{
	URebirthAssetManager* This = Cast<URebirthAssetManager>(GEngine->AssetManager);
	if (This)
	{
		return *This;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be GameAssetManager!"));
		return *NewObject<URebirthAssetManager>(); // never calls this
	}
}

UItem* URebirthAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);
	UItem* LoadedItem = Cast<UItem>(ItemPath.TryLoad());
	if (bLogWarning && LoadedItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load item for identifier %s!"), *PrimaryAssetId.ToString());
	}
	return LoadedItem;
}

UGameplayLevelInfo* URebirthAssetManager::ForceLoadLevelInfo(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{
	FSoftObjectPath LevelInfoPath = GetPrimaryAssetPath(PrimaryAssetId);
	UGameplayLevelInfo* LoadedLevelInfo = Cast<UGameplayLevelInfo>(LevelInfoPath.TryLoad());
	if (bLogWarning && LoadedLevelInfo == nullptr)
	{
		/*UE_LOG(LogTemp, Warning, TEXT("Failed to load level info for identifier %s!"), *PrimaryAssetId.ToString());*/
		return NewObject<UGameplayLevelInfo>();
	}
	return LoadedLevelInfo;
}



