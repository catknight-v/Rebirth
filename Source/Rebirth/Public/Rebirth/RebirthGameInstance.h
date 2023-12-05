// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Characters/CombatCharacterDefaultInventory.h"
#include "Rebirth/DefaultTag.h"
#include "RebirthGameInstance.generated.h"

class URebirthSaveGame;

/**
 * 
 */
UCLASS()
class REBIRTH_API URebirthGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	URebirthGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<UCombatCharacterDefaultInventory> InventoryClass;

	UFUNCTION(BlueprintCallable)
	UCombatCharacterDefaultInventory* GetDefaultInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<UDefaultTag> DefaultTagClass;

	UFUNCTION(BlueprintCallable)
	UDefaultTag* GetDefaultTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FPrimaryAssetType, int32> AssetSlotsPerType;

	UPROPERTY(BlueprintReadWrite, Category = Save)
	FString SaveSlot;

	UPROPERTY(BlueprintReadWrite, Category = Save)
	int32 SaveUserIndex;

	UFUNCTION(BlueprintCallable, Category = Save)
	URebirthSaveGame* GetCurrentSaveGame();

	UFUNCTION(BlueprintCallable, Category = Save)
	void SetSavingEnabled(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = Save)
	bool LoadOrCreateSaveGame();

	UFUNCTION(BlueprintCallable, Category = Save)
	bool HandleSaveGameLoaded(USaveGame* SaveGameObject);

	UFUNCTION(BlueprintCallable, Category = Save)
	bool WriteSaveGame();

	UFUNCTION(BlueprintCallable, Category = Save)
	void ResetSaveGame();

protected:

	UPROPERTY()
	URebirthSaveGame* CurrentSaveGame;

	/** Rather it will attempt to actually save to disk */
	UPROPERTY()
	bool bSavingEnabled;

	/** True if we are in the middle of doing a save */
	UPROPERTY()
	bool bCurrentlySaving;

	/** True if another save was requested during a save */
	UPROPERTY()
	bool bPendingSaveRequested;

	/** Called when the async save happens */
	virtual void HandleAsyncSave(const FString& SlotName, const int32 UserIndex, bool bSuccess);


};
