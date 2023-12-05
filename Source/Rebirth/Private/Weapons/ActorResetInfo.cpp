// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ActorResetInfo.h"

UActorResetInfo::UActorResetInfo(){}

void UActorResetInfo::ActorReset()
{
	ActorSet->Remove(Actor);
}

void UActorResetInfo::Init(AActor* OtherActor, TSet<AActor*>* Set)
{
	Actor = OtherActor;
	ActorSet = Set;
}
