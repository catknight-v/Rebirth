// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/GameplayLevelInfo.h"

FPrimaryAssetId UGameplayLevelInfo::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(LevelType, GetFName());
}