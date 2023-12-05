// Fill out your copyright notice in the Description page of Project Settings.


#include "Rebirth/RebirthSaveGame.h"
#include "Rebirth/RebirthAssetManager.h"
#include "Items/Item.h"
#include "Gameplay/GameplayLevelInfo.h"
#include "Rebirth/RebirthAssetManager.h"

void URebirthSaveGame::LoadInventroyData(FKnapsack& Knapsack)
{
	Knapsack.Reset();
	URebirthAssetManager& AssetManager = URebirthAssetManager::Get();
	for (const TPair<FPrimaryAssetId, FItemData>& Pair : InventoryData)
	{
		UItem* Item = AssetManager.ForceLoadItem(Pair.Key);
		Knapsack.AddInventoryItem(Item, Pair.Value.ItemCount);
	}
}

void URebirthSaveGame::UpdateInventroyData(const FKnapsack& Knapsack)
{
	for (const TPair<UItem*, FItemData>& Pair : Knapsack.InventoryData)
	{
		InventoryData.Add(Pair.Key->GetPrimaryAssetId(), Pair.Value);
	}
}

int32 URebirthSaveGame::StatusInquiry(FName StatusName, int32 Default)
{
	int32* Value = StatusInquiryMap.Find(StatusName);
	if (Value)
	{
		return *Value;
	}
	StatusInquiryMap.Add(StatusName, Default);
	return Default;
}

void URebirthSaveGame::StatusUpdate(FName StatusName, int32 Value)
{
	StatusInquiryMap.Add(StatusName, Value);
}

void URebirthSaveGame::SetCurrentLevel(FPrimaryAssetId Level)
{
	CurrentLevel = Level;
}

FName URebirthSaveGame::GetCurrentLevelName()
{
	URebirthAssetManager& AssetManager = URebirthAssetManager::Get();
	UGameplayLevelInfo* LevelInfo = AssetManager.ForceLoadLevelInfo(CurrentLevel);
	return LevelInfo->LevelName;
}

FVector URebirthSaveGame::GetCurrentLevelStart()
{
	URebirthAssetManager& AssetManager = URebirthAssetManager::Get();
	UGameplayLevelInfo* LevelInfo = AssetManager.ForceLoadLevelInfo(CurrentLevel);
	return LevelInfo->PlayerStart;
}
