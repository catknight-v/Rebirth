// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rebirth.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "Rebirth/RebirthAssetManager.h"
#include "Item.generated.h"

class UGameplayAbility;


UCLASS(Abstract, BlueprintType)
class REBIRTH_API UItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UItem() {}

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Item)
	FPrimaryAssetType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FSlateBrush ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 MaxCount;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Item)
	bool IsConsumable() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	TArray<TSubclassOf<UGameplayAbility>> GrantedAbilities;

	UFUNCTION(BlueprintCallable, Category = Item)
	FString GetIdentifierString() const;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
};
