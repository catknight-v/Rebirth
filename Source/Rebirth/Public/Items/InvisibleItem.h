// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/Item.h"
#include "InvisibleItem.generated.h"

/**
 * 
 */
UCLASS()
class REBIRTH_API UInvisibleItem : public UItem
{
	GENERATED_BODY()
	
public:
	UInvisibleItem()
	{
		ItemType = URebirthAssetManager::InvisibleItemType;
	}

};
