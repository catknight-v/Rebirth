// Fill out your copyright notice in the Description page of Project Settings.


#include "TopSideView/RebirthPlayerCameraManager.h"

void ARebirthPlayerCameraManager::BeginPlay()
{
	//spawn view actor
}

void ARebirthPlayerCameraManager::UpdateCamera(float DeltaTime)
{
	//Tick Update ViewActor


	Super::UpdateCamera(DeltaTime);
}

void ARebirthPlayerCameraManager::LookUp(float Rate)
{
	TopSideViewInfo.CurrentRate += Rate;
	TopSideViewInfo.CurrentRate = FMath::Clamp(TopSideViewInfo.CurrentRate, TopSideViewInfo.MinTopRate, TopSideViewInfo.MaxTopRate);
}

void ARebirthPlayerCameraManager::SetTargetActor(AActor* Actor)
{
	TargetActor = Actor;
}

void ARebirthPlayerCameraManager::SetFollowActor(AActor* Actor)
{
	FollowActor = Actor;
}
