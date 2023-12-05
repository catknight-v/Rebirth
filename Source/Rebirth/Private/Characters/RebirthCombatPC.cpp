// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RebirthCombatPC.h"
#include "Interaction/InteractionComponent.h"
#include "Rebirth/RebirthGameInstance.h"
#include "Rebirth/RebirthAssetManager.h"
#include "Rebirth/RebirthSaveGame.h"
#include "Items/Item.h"
#include "Items/WeaponItem.h"
#include "Weapons/MeleeWeaponActor.h"

ARebirthCombatPC::ARebirthCombatPC()
{
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	InteractionComponent->SetupAttachment(GetRootComponent());
	//InteractionComponent->SetInteractionOwner(this);
}

void ARebirthCombatPC::CombatCharacterInit()
{
	LoadPlayerItems();
	InitAbilities();
	ActivateInitAbilities();
}

void ARebirthCombatPC::LoadPlayerItems()
{
	//LoadDefaultItems();
	UWorld* World = GetWorld();
	ULevel* Level = GetLevel();

	URebirthGameInstance* GameInstance = Cast<URebirthGameInstance>(World->GetGameInstance());
	URebirthSaveGame* SaveGame = GameInstance->GetCurrentSaveGame();
	if (SaveGame->InventoryData.Num() == 0)
	{
		LoadDefaultItems();
		SavePlayerItems();
	}
	else
	{
		//¶ÁÈ¡¿â´æ
		SaveGame->LoadInventroyData(Knapsack);
	}
	SpawnInventoryWeapon();
}

void ARebirthCombatPC::SavePlayerItems()
{
	//TODO:±£´æ¿â´æ
	URebirthGameInstance* GameInstance = Cast<URebirthGameInstance>(GetWorld()->GetGameInstance());
	URebirthSaveGame* SaveGame = GameInstance->GetCurrentSaveGame();
	SaveGame->UpdateInventroyData(Knapsack);
	GameInstance->WriteSaveGame();
}

bool ARebirthCombatPC::IsMeleeWeaponOn()
{
	return MeleeWeapon != nullptr;
}

void ARebirthCombatPC::GetItem(FPrimaryAssetId WeaponId, int32 Count)
{
	URebirthGameInstance* GameInstance = Cast<URebirthGameInstance>(GetGameInstance());
	URebirthSaveGame* SaveGame = GameInstance->GetCurrentSaveGame();
	URebirthAssetManager& AssetManager = URebirthAssetManager::Get();
	UItem* Item = AssetManager.ForceLoadItem(WeaponId);
	Knapsack.AddInventoryItem(Item, Count);

	for (TSubclassOf<UGameplayAbility> Ability : Item->GrantedAbilities)
	{
		GetAbilitySystemComponent()->GiveAbility(Ability);
	}

	if (Item->ItemType == URebirthAssetManager::WeaponItemType)
	{
		//Spawn
		UWeaponItem* WeaponItem = Cast<UWeaponItem>(Item);
		MeleeWeapon = GetWorld()->SpawnActor(WeaponItem->WeaponActor.Get());
		MeleeWeapon->SetInstigator(this);
		FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, true);
		AMeleeWeaponActor* MeleeWeaponActor = Cast<AMeleeWeaponActor>(MeleeWeapon);
		MeleeWeaponActor->AttachToComponent(GetMesh(), Rules, MeleeWeaponActor->MeshSocketName);
	}

	SavePlayerItems();
}

void ARebirthCombatPC::SpawnInventoryWeapon()
{
	for (TPair<UItem*, FItemData> Pair : Knapsack.InventoryData)
	{
		//UE_LOG(LogTemp, Display, TEXT("SpawnInventoryWeapon"));
		UWeaponItem* WeaponItem = Cast<UWeaponItem>(Pair.Key);
		if (WeaponItem)
		{
			if (WeaponItem->WeaponActor.Get()->IsChildOf(AMeleeWeaponActor::StaticClass()))
			{
				MeleeWeapon = GetWorld()->SpawnActor(WeaponItem->WeaponActor.Get());
				MeleeWeapon->SetInstigator(this);
				FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, true);
				AMeleeWeaponActor* MeleeWeaponActor = Cast<AMeleeWeaponActor>(MeleeWeapon);
				MeleeWeaponActor->AttachToComponent(GetMesh(), Rules, MeleeWeaponActor->MeshSocketName);
				break;
			}
		}
	}
}
