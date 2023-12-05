// Fill out your copyright notice in the Description page of Project Settings.


#include "Rebirth/RebirthGameModeBase.h"
#include "Perform/ActActor.h"
#include "Controllers/RebirthPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

//int32 ARebirthGameModeBase::PlayAnAct(TSubclassOf<AActActor> ActClass)
//{
//    AActActor* Act = Cast<AActActor>(ActClass.Get()->GetDefaultObject());
//    CurrentAct = Act;
//    CurrentAct->FindActors();
//    CurrentAct->ActAction();
//	return true;
//}
//
//int32 ARebirthGameModeBase::SwithGameMode(EGameModeType GameMode)
//{
//	if (GameMode == CurrentGameModeType)
//	{
//		return false;
//	}
//	else if (GameMode == EGameModeType::Director)
//	{
//		CurrentGameModeType = EGameModeType::Director;
//	}
//	else
//	{
//		CurrentGameModeType = EGameModeType::Free;
//	}
//
//	return true;
//}
//
//void ARebirthGameModeBase::SetPlayerControllable(bool bActionControllable)
//{
//	APlayerController* Controller = UGameplayStatics::GetPlayerController(GWorld, 0);
//	ARebirthPlayerController* PlayerController = Cast<ARebirthPlayerController>(Controller);
//	if (PlayerController)
//	{
//		PlayerController->bActionControllable = bActionControllable;
//	}
//}
//
//void ARebirthGameModeBase::Interact()
//{
//    //需要判断当前的游戏模式
//}
