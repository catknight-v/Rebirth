// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorResetInfo.generated.h"

UCLASS()
class REBIRTH_API UActorResetInfo : public UObject
{
	GENERATED_BODY()

public:
	UActorResetInfo();

	AActor* Actor;
	TSet<AActor*>* ActorSet;

	void ActorReset();
	void Init(AActor* OtherActor, TSet<AActor*>* Set);
};
