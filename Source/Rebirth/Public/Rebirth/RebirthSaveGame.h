// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Items/ItemTypes.h"
#include "RebirthSaveGame.generated.h"

class UGameplayLevelInfo;

/**
 * 
 */
UCLASS()
class REBIRTH_API URebirthSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	URebirthSaveGame(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SaveGame)
	TMap<FPrimaryAssetId, FItemData> InventoryData;

	UFUNCTION(BlueprintCallable, Category = SaveGame)
	void LoadInventroyData(FKnapsack& Knapsack);

	UFUNCTION(BlueprintCallable, Category = SaveGame)
	void UpdateInventroyData(const FKnapsack& Knapsack);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SaveGame)
	TMap<FName, int32> StatusInquiryMap;

	UFUNCTION(BlueprintCallable, Category = SaveGame)
	int32 StatusInquiry(FName StatusName, int32 Default = 0);

	UFUNCTION(BlueprintCallable, Category = SaveGame)
	void StatusUpdate(FName StatusName, int32 Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SaveGame)
	FPrimaryAssetId CurrentLevel;

	UFUNCTION(BlueprintCallable, Category = SaveGame)
	void SetCurrentLevel(FPrimaryAssetId Level);

	UFUNCTION(BlueprintCallable, Category = SaveGame)
	FName GetCurrentLevelName();

	UFUNCTION(BlueprintCallable, Category = SaveGame)
	FVector GetCurrentLevelStart();

	
};
