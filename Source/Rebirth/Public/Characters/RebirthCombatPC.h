// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RebirthCombatCharacterBase.h"
#include "RebirthCombatPC.generated.h"

class UInteractionComponent;

/**
 * 
 */
UCLASS()
class REBIRTH_API ARebirthCombatPC : public ARebirthCombatCharacterBase
{
	GENERATED_BODY()
	
public:
	ARebirthCombatPC();

	virtual void CombatCharacterInit() override;

	UFUNCTION(BlueprintCallable, Category = Player)
	virtual void LoadPlayerItems();

	UFUNCTION(BlueprintCallable, Category = Player)
	virtual void SavePlayerItems();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	UInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	AActor* MeleeWeapon;

	/*true if MeleeWeapon != nullptr */
	UFUNCTION(BlueprintCallable, Category = Player)
	bool IsMeleeWeaponOn();

	UFUNCTION(BlueprintCallable, Category = Player)
	void GetItem(FPrimaryAssetId WeaponId, int32 Count);

	UFUNCTION(BlueprintCallable, Category = Player)
	void SpawnInventoryWeapon();

};
