// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/ItemTypes.h"
#include "Items/Item.h"

bool FKnapsack::GetInventoryItemData(UItem* Item, FItemData& ItemData) const
{
	const FItemData* FoundItem = InventoryData.Find(Item);

	if (FoundItem)
	{
		ItemData = *FoundItem;
		return true;
	}

	ItemData = FItemData(0);
	return false;
}

bool FKnapsack::AddInventoryItem(UItem* NewItem, int32 ItemCount, bool bAutoSlot)
{
	if (!NewItem)
	{
		return false;
	}

	if (ItemCount <= 0)
	{
		return false;
	}

	FItemData OldData;
	GetInventoryItemData(NewItem, OldData);

	FItemData NewData = OldData;
	NewData.UpdateItemData(FItemData(ItemCount), NewItem->MaxCount);

	if (OldData != NewData)
	{
		InventoryData.Add(NewItem, NewData);
		return true;
	}

	return false;
}

bool FKnapsack::RemoveInventoryItem(UItem* RemovedItem, int32 RemoveCount)
{
	if (!RemovedItem)
	{
		return false;
	}

	FItemData NewData;
	GetInventoryItemData(RemovedItem, NewData);
	if (!NewData.IsValid())
	{
		return false;
	}

	if (RemoveCount <= 0)
	{
		//É¾³ýËùÓÐ
		NewData.ItemCount = 0;
	}
	else
	{
		NewData.ItemCount -= RemoveCount;
	}

	if (NewData.ItemCount > 0)
	{
		InventoryData.Add(RemovedItem, NewData);
	}
	else
	{
		InventoryData.Remove(RemovedItem);
	}

	return true;
}

void FKnapsack::Reset()
{
	InventoryData.Reset();
}
