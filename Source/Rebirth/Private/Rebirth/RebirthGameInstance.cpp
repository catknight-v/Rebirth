// Fill out your copyright notice in the Description page of Project Settings.


#include "Rebirth/RebirthGameInstance.h"
#include "Rebirth/RebirthSaveGame.h"
#include "Rebirth/RebirthAssetManager.h"
#include "Kismet/GameplayStatics.h"

URebirthGameInstance::URebirthGameInstance()
    : SaveSlot(TEXT("SaveGame"))
    , SaveUserIndex(0)
    , bSavingEnabled(true)
    , bCurrentlySaving(false)
    , bPendingSaveRequested(false)
{}

UCombatCharacterDefaultInventory* URebirthGameInstance::GetDefaultInventory()
{
    if (InventoryClass.Get())
    {
        return Cast<UCombatCharacterDefaultInventory>(InventoryClass.Get()->GetDefaultObject());
    }
    return nullptr;
}

UDefaultTag* URebirthGameInstance::GetDefaultTag()
{
    if (DefaultTagClass.Get())
    {
        return Cast<UDefaultTag>(DefaultTagClass.Get()->GetDefaultObject());
    }
    return nullptr;
}

URebirthSaveGame* URebirthGameInstance::GetCurrentSaveGame()
{
    if (!CurrentSaveGame)
    {
        if (!LoadOrCreateSaveGame())
        {
            UE_LOG(LogTemp, Warning, TEXT("load failed"));
        }
    }
    return CurrentSaveGame;
}

void URebirthGameInstance::SetSavingEnabled(bool bEnabled)
{
    bSavingEnabled = bEnabled;
}

bool URebirthGameInstance::LoadOrCreateSaveGame()
{
    URebirthSaveGame* LoadedSave = nullptr;
    if (UGameplayStatics::DoesSaveGameExist(SaveSlot, SaveUserIndex) && bSavingEnabled)
    {
        LoadedSave = Cast<URebirthSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, SaveUserIndex));
    }

    return HandleSaveGameLoaded(LoadedSave);
}

bool URebirthGameInstance::HandleSaveGameLoaded(USaveGame* SaveGameObject)
{
    bool bLoaded = false;
    if (!bSavingEnabled)
    {
        SaveGameObject = nullptr;
    }

    CurrentSaveGame = Cast<URebirthSaveGame>(SaveGameObject);

    if (CurrentSaveGame)
    {
        bLoaded = true;
    }
    else
    {
        CurrentSaveGame = Cast<URebirthSaveGame>(UGameplayStatics::CreateSaveGameObject(URebirthSaveGame::StaticClass()));
    }
    return bLoaded;
}

bool URebirthGameInstance::WriteSaveGame()
{
    if (bSavingEnabled)
    {
        if (bCurrentlySaving)
        {
            bPendingSaveRequested = true;
            return true;
        }
        bCurrentlySaving = true;
        UGameplayStatics::AsyncSaveGameToSlot(GetCurrentSaveGame(), SaveSlot, SaveUserIndex, FAsyncSaveGameToSlotDelegate::CreateUObject(this, &URebirthGameInstance::HandleAsyncSave));
        return true;
    }
    return false;
}

void URebirthGameInstance::ResetSaveGame()
{
    HandleSaveGameLoaded(nullptr);
}

void URebirthGameInstance::HandleAsyncSave(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
    ensure(bCurrentlySaving);
    bCurrentlySaving = false;

    if (bPendingSaveRequested)
    {
        bPendingSaveRequested = false;
        WriteSaveGame();
    }
}
