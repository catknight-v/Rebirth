// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/MeleeWeaponActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Characters/RebirthCombatCharacterBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Characters/RebirthCombatCharacterBase.h"

// Sets default values
AMeleeWeaponActor::AMeleeWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));

	USphereComponent* SphereRoot = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	SetRootComponent(SphereRoot);
	SphereRoot->SetGenerateOverlapEvents(false);
	CapsuleCollision->SetupAttachment(GetRootComponent());
	SkeletalMesh->SetupAttachment(GetRootComponent());
	CapsuleCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	CapsuleCollision->SetGenerateOverlapEvents(true);
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMeleeWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this,&AMeleeWeaponActor::ActorBeginOverlapped);
	OnActorEndOverlap.AddDynamic(this,&AMeleeWeaponActor::ActorEndOverlapped);

	//OnActorBeginOverlap
	//AVolume;
	
}

void AMeleeWeaponActor::BeginWeaponAttack(FGameplayTag EventTag)
{
	bAttacking = true;
	AttackEventTag = EventTag;
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	//CapsuleCollision->SetCollisionResponseToAllChannels(ECR_Overlap);
	//CapsuleCollision->SetCollisionResponseToChannel(ECollisionChannel::)
	
}

void AMeleeWeaponActor::EndWeaponAttack()
{
	bAttacking = false;
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMeleeWeaponActor::ActorBeginOverlapped(AActor* OverlappedActor, AActor* OtherActor)
{
	//先判断OtherActor是否Combat
	if (Cast<ARebirthCombatCharacterBase>(OtherActor))
	{
		//再判断是否可以产生伤害，此处的设置是，不同class就可以产生伤害
		if (GetInstigator()->GetClass() != OtherActor->GetClass() && bAttacking)
		{
			//是否仍处于攻击对象
			if (AttackingActors.Find(OtherActor) == nullptr)
			{
				//先让Other加入Set
				AttackingActors.Add(OtherActor);
				//再向Instigator发送Event
				FGameplayEventData Payload;
				Payload.Target = OtherActor;
				Payload.Instigator = GetInstigator();
				/*FHitResult HitResult;
				HitResult.Actor
				HitResult.Location = OverlappedActor->GetActorLocation();
				Payload.ContextHandle.AddHitResult(HitResult);*/
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetInstigator(), AttackEventTag, Payload);
			}
		}
	}
}

void AMeleeWeaponActor::ActorEndOverlapped(AActor* OverlappedActor, AActor* OtherActor)
{
	UActorResetInfo* ActorResetInfo = NewObject<UActorResetInfo>(this);
	ActorResetInfo->Init(OtherActor, &AttackingActors);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, ActorResetInfo, &UActorResetInfo::ActorReset, 0.2f);
}

