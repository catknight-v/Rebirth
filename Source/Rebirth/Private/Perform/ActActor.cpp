// Fill out your copyright notice in the Description page of Project Settings.


#include "Perform/ActActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/DataTable.h"
#include "Perform/DialogueUserWidget.h"
#include "Controllers/RebirthPlayerController.h"

// Sets default values
AActActor::AActActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AActActor::SetDirector(ARebirthPlayerController* Controller)
{
	PlayerController = Controller;
}

ARebirthPlayerController* AActActor::GetDirector()
{
	return PlayerController;
}

UDialogueUserWidget* AActActor::GetDialogueUserWidget()
{
	return DialogueUserWidget;
}

void AActActor::SetPlayerControllable(bool bControllable)
{
	if (PlayerController)
	{
		PlayerController->SetActionControllable(bControllable);
	}
}

void AActActor::SetControllerGameMode(EGameModeType Mode)
{
	if (PlayerController)
	{
		PlayerController->SetGameMode(Mode);
	}
}

void AActActor::ControllerPreAct()
{
	SetPlayerControllable(false);
	SetControllerGameMode(EGameModeType::Director);
}

void AActActor::ControllerActCut()
{
	SetPlayerControllable(true);
	SetControllerGameMode(EGameModeType::Free);
}

FActorInPlaceInfo AActActor::FindActor(FGameplayTag ActorTag)
{
	TArray<AActor*> Actors;
	FActorInPlaceInfo ActorInPlaceInfo;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), ActorTag.GetTagName(), Actors);
	for (AActor* Actor : Actors)
	{
		ActorInPlaceInfo.Actor = Actor;
		ActorInPlaceInfo.bInPlace = true;
		break;
	}
	return ActorInPlaceInfo;
}

UDialogueUserWidget* AActActor::BeginDialogue(TSubclassOf<UDialogueUserWidget> Widget, UDataTable* DataTable, int32 StartIndex)
{
	DialogueUserWidget = CreateWidget<UDialogueUserWidget>(PlayerController, Widget.Get());
	//UW不允许使用CDO
	//UDialogueUserWidget* DialogueUserWidget = Cast<UDialogueUserWidget>(Widget.GetDefaultObject());
	DialogueUserWidget->BeginDialogue(DataTable, StartIndex);
	return DialogueUserWidget;
}
