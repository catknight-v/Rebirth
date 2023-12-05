// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rebirth.h"
#include "UObject/PrimaryAssetId.h"
#include "ItemTypes.generated.h"

class UItem;

USTRUCT(BlueprintType)
struct REBIRTH_API FItemData
{
	GENERATED_BODY()

public:
	FItemData()
		: ItemCount(1)
	{}

	FItemData(int32 InItemCount)
		:ItemCount(InItemCount)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemCount;

	bool IsValid() const
	{
		return ItemCount > 0;
	}

	void UpdateItemData(const FItemData& Other, int32 MaxCount)
	{
		if (MaxCount <= 0)
		{
			MaxCount = MAX_int32;
		}

		ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1, MaxCount);
	}

	bool operator==(const FItemData& Other) const
	{
		return ItemCount == Other.ItemCount;
	}

	bool operator!=(const FItemData& Other) const
	{
		return !(*this == Other);
	}

};

USTRUCT(BlueprintType)
struct REBIRTH_API FKnapsack
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<UItem*, FItemData> InventoryData;

	bool GetInventoryItemData(UItem* Item, FItemData& ItemData) const;
	
	bool AddInventoryItem(UItem* NewItem, int32 ItemCount = 1, bool bAutoSlot = true);
	
	bool RemoveInventoryItem(UItem* RemovedItem, int32 RemoveCount = 1);
	
	void Reset();
};
