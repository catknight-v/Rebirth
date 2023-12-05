// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RebirthCombatNPC.h"
#include "Components/WidgetComponent.h"

TSet<ARebirthCombatNPC*> ARebirthCombatNPC::Enemies;

ARebirthCombatNPC::ARebirthCombatNPC()
{
	TargetWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("TargetWidget"));
	TargetWidget->SetupAttachment(GetRootComponent());
	TargetWidget->SetWidgetSpace(EWidgetSpace::Screen);

	//bUseControllerRotationYaw = true;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void ARebirthCombatNPC::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RemoveSelfFromEnemies();
	Super::EndPlay(EndPlayReason);
}

void ARebirthCombatNPC::BeginPlay()
{
	Super::BeginPlay();
	AddSelfToEnemies();
	TargetWidget->SetVisibility(false);
}

void ARebirthCombatNPC::GetAllEnemies(TArray<ARebirthCombatNPC*>& OutEnemies)
{
	OutEnemies.Reset();
	for (ARebirthCombatNPC* Enemy : Enemies)
	{
		OutEnemies.Add(Enemy);
	}
}

void ARebirthCombatNPC::AddSelfToEnemies()
{
	Enemies.Add(this);
}

void ARebirthCombatNPC::RemoveSelfFromEnemies()
{
	Enemies.Remove(this);
}

void ARebirthCombatNPC::SetSelfTarget()
{
	TargetWidget->SetVisibility(true);
}

void ARebirthCombatNPC::RemoveSelfTarget()
{
	TargetWidget->SetVisibility(false);
}

void ARebirthCombatNPC::HandleDeath(float DamageAmount, const FHitResult& HitInfo, const FGameplayTagContainer& DamageTags, ARebirthCombatCharacterBase* InstigatorCharacter, AActor* DamageCauser)
{
	Super::HandleDeath(DamageAmount, HitInfo, DamageTags, InstigatorCharacter, DamageCauser);
	RemoveSelfTarget();
	RemoveSelfFromEnemies();
}
