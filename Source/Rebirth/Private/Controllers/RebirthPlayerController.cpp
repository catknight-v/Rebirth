// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/RebirthPlayerController.h"
#include "TopSideView/TopSideViewTargetActor.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Characters/RebirthCombatPC.h"
#include "Rebirth/RebirthGameInstance.h"
#include "Rebirth/DefaultTag.h"
#include "Interaction/InteractionComponent.h"
#include "Perform/ActActor.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/RebirthCombatNPC.h"

void ARebirthPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ViewTargetActor = GetWorld()->SpawnActor<ATopSideViewTargetActor>(/*FollowActorClass.Get()*/);
	AnimTargetActor = GetWorld()->SpawnActor<ATopSideViewTargetActor>();
	PlayerCameraManager->SetViewTarget(ViewTargetActor);
	bActionControllable = true;
	CurrentMode = EGameModeType::Free;
	bUsingAnimaTargetActor = false;
	/*GetRootComponent()->SetupAttachment(GetCharacter()->GetRootComponent());*/
	//SpawnPlayerCameraManager
}

void ARebirthPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//绑定操作
	InputComponent->BindAxis("MoveForward", this, &ARebirthPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARebirthPlayerController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &ARebirthPlayerController::LookUp);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARebirthPlayerController::Jump);
	InputComponent->BindAction("Interact", IE_Pressed, this, &ARebirthPlayerController::Interact);
	InputComponent->BindAction("Melee", IE_Pressed, this, &ARebirthPlayerController::Melee);
	InputComponent->BindAction("Dodge", IE_Pressed, this, &ARebirthPlayerController::Dodge);

	InputComponent->BindAction("SearchTarget", IE_Pressed, this, &ARebirthPlayerController::SearchTarget);
	InputComponent->BindAxis("SearchTargetX", this, &ARebirthPlayerController::SearchTargetX);
	//AActor::EnableInput()
	//InputComponent->set
	//Possess()
	//PushInputComponent();
	//USceneComponent::SetupAttachment();
	//USceneComponent::OnAttachMentChanged;
	//USceneComponent::ModifiedAttachChildren();
	//USceneComponent::UpdateComponentToWorld();
	//USceneComponent::SetRelativeLocationAndRotation();
	UCameraComponent;
	AActor::CalcCamera;
	USceneComponent::SetRelativeTransform;
	//USceneComponent::SetRelativeLocationAndRotation;
}

void ARebirthPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//SetActorLocationAndRotation(GetCharacter()->GetActorLocation(), GetCharacter()->GetActorRotation());

	UpdateViewTarget();
	UpdateTarget();
}

ATopSideViewTargetActor* ARebirthPlayerController::GetViewTargetActor()
{
	return ViewTargetActor;
}

ATopSideViewTargetActor* ARebirthPlayerController::EnterAnimView()
{
	bUsingAnimaTargetActor = true;
	AnimTargetActor->SetViewInfo(TopSideViewInfo);
	AnimTargetActor->SetActorLocation(GetCharacter()->GetActorLocation());
	SetViewTarget(AnimTargetActor);
	return AnimTargetActor;
}

void ARebirthPlayerController::QuitAnimView()
{
	bUsingAnimaTargetActor = false;
	SetViewTargetWithBlend(ViewTargetActor, 1.f);

	//APlayerCameraManager::AddPo
}

AActor* ARebirthPlayerController::GetTarget()
{
	return Target;
}

void ARebirthPlayerController::FindTarget(int32 Mode)
{
	/*UDefaultTag* DefaultTag = GetDefaultTag();
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), DefaultTag->PawnEnemyTag.GetTagName(), OutActors);*/

	TArray<ARebirthCombatNPC*> Enemies;
	ARebirthCombatNPC::GetAllEnemies(Enemies);
	//TODO: Z 限制?

	if (Mode == 0 && Target == nullptr)
	{
		// max sence Distance
		float MaxSenceDistance = 4000.f;

		float MinTargetDistance = MaxSenceDistance;
		ARebirthCombatNPC* FinalTarget = nullptr;
		FVector PlayerLocation = GetCharacter()->GetActorLocation();
		for (ARebirthCombatNPC* Enemy : Enemies)
		{
			float Distance = FVector::Distance(Enemy->GetActorLocation(), PlayerLocation);
			if (Distance < MinTargetDistance)
			{
				FinalTarget = Enemy;
				MinTargetDistance = Distance;
			}
		}

		if (FinalTarget)
		{
			Target = FinalTarget;
			FinalTarget->SetSelfTarget();
		}
	}
	else if (Mode != 0 && Target)
	{
		float MaxSenceDistance = 4000.f;
		ARebirthCombatNPC* FinalTarget = nullptr;
		FVector PlayerLocation = GetCharacter()->GetActorLocation();
		float OldTargetX = Target->GetActorLocation().X;
		float MinTargetDistanceX = MaxSenceDistance;
		for (ARebirthCombatNPC* Enemy : Enemies)
		{
			float Distance = FVector::Distance(Enemy->GetActorLocation(), PlayerLocation);
			if (Enemy == Target || Distance > MaxSenceDistance)
			{
				continue;
			}
			float DistanceX = Enemy->GetActorLocation().X - OldTargetX;
			if (DistanceX * Mode <= 0 && FMath::Abs(DistanceX) < MinTargetDistanceX)
			{
				FinalTarget = Enemy;
				MinTargetDistanceX = FMath::Abs(DistanceX);
			}
		}
		
		if (FinalTarget)
		{
			ARebirthCombatNPC* NPC = Cast<ARebirthCombatNPC>(Target);
			if (NPC)
			{
				NPC->RemoveSelfTarget();
			}
			Target = FinalTarget;
			FinalTarget->SetSelfTarget();
		}
	}
}

void ARebirthPlayerController::SetActionControllable(bool bControllable)
{
	bActionControllable = bControllable;
}

void ARebirthPlayerController::SetGameMode(EGameModeType NewMode)
{
	CurrentMode = NewMode;
}

int32 ARebirthPlayerController::PlayAnAct(TSubclassOf<AActActor> ActClass)
{
	AActActor* Act = GetWorld()->SpawnActor<AActActor>(ActClass.Get());
	//AActActor* Act = ActClass.GetDefaultObject();
	CurrentAct = Act;
	CurrentAct->SetDirector(this);
	CurrentAct->ActPrepare();
	CurrentAct->ActAction();
	return true;
}

void ARebirthPlayerController::PushForwardInteraction()
{
	//推进交互
	if (CurrentAct)
	{
		if (CurrentAct->PushForward() == -1)
		{
			SetGameMode(EGameModeType::Free);
			SetActionControllable(true);
		}
	}
}

UDefaultTag* ARebirthPlayerController::GetDefaultTag()
{
	//TODO:逻辑包装
	URebirthGameInstance* GameInstance = Cast<URebirthGameInstance>(GetWorld()->GetGameInstance());
	UDefaultTag* DefaultTag = nullptr;
	if (GameInstance)
	{
		DefaultTag = GameInstance->GetDefaultTag();
	}
	return DefaultTag;
}

void ARebirthPlayerController::UpdateViewTarget()
{
	if (GetCharacter())
	{
		ViewTargetActor->SetActorLocation(GetCharacter()->GetActorLocation());
	}
	ViewTargetActor->SetViewInfo(TopSideViewInfo);
}

void ARebirthPlayerController::UpdateTarget()
{
	//TODO:更新Target如距离过远，Target死亡等应该取消Target
	if (Target)
	{
		ARebirthCombatNPC* NPC = Cast<ARebirthCombatNPC>(Target);
		bool bTargetShouldRemove = false;
		if (NPC)
		{
			float MaxSenceDistance = 4000.f;
			if (!bTargetShouldRemove && FVector::Distance(Target->GetActorLocation(), GetCharacter()->GetActorLocation()) > MaxSenceDistance)
			{
				bTargetShouldRemove = true;
			}
			if (!bTargetShouldRemove && !NPC->IsAlive())
			{
				bTargetShouldRemove = true;
			}

			if (bTargetShouldRemove)
			{
				NPC->RemoveSelfTarget();
				Target = nullptr;
			}
		}
	}
}

void ARebirthPlayerController::MoveForward(float Value)
{
	ARebirthCombatCharacterBase* PlayerCharacter = Cast<ARebirthCombatCharacterBase>(GetCharacter());
	static FVector Direction(0, 1, 0);
	if (PlayerCharacter && PlayerCharacter->IsActionable() && PlayerCharacter->IsAlive() && bActionControllable)
	{
		GetCharacter()->AddMovementInput(Direction, Value);
	}
}
void ARebirthPlayerController::MoveRight(float Value)
{
	ARebirthCombatCharacterBase* PlayerCharacter = Cast<ARebirthCombatCharacterBase>(GetCharacter());
	static FVector Direction(-1, 0, 0);
	if (PlayerCharacter && PlayerCharacter->IsActionable() && PlayerCharacter->IsAlive() && bActionControllable)
	{
		GetCharacter()->AddMovementInput(Direction, Value);
	}
}
void ARebirthPlayerController::LookUp(float Rate)
{
	TopSideViewInfo.CurrentRate += Rate;
	TopSideViewInfo.CurrentRate = FMath::Clamp(TopSideViewInfo.CurrentRate, TopSideViewInfo.MinTopRate, TopSideViewInfo.MaxTopRate);
}
void ARebirthPlayerController::Jump()
{
	UDefaultTag* DefaultTag = GetDefaultTag();
	ARebirthCombatPC* PlayerCharacter = Cast<ARebirthCombatPC>(GetCharacter());
	FGameplayTagContainer JumpTags;
	if (DefaultTag)
	{
		JumpTags.AddTag(DefaultTag->AbilityJumpTag);
	}
	if (PlayerCharacter && PlayerCharacter->IsActionable() && PlayerCharacter->IsAlive() && bActionControllable)
	{
		PlayerCharacter->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(JumpTags);
	}
}
void ARebirthPlayerController::Melee()
{
	UDefaultTag* DefaultTag = GetDefaultTag();
	ARebirthCombatPC* PlayerCharacter = Cast<ARebirthCombatPC>(GetCharacter());
	FGameplayTagContainer MeleeTags;
	if (DefaultTag)
	{
		MeleeTags.AddTag(DefaultTag->AbilityMeleeTag);
	}
	if (PlayerCharacter && PlayerCharacter->IsActionable() && PlayerCharacter->IsAlive() && bActionControllable)
	{
		if (Target)
		{
			PlayerCharacter->FaceToInstantly(Target->GetActorLocation());
		}
		PlayerCharacter->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(MeleeTags);
	}
}

void ARebirthPlayerController::Dodge()
{
	UDefaultTag* DefaultTag = GetDefaultTag();
	ARebirthCombatPC* PlayerCharacter = Cast<ARebirthCombatPC>(GetCharacter());
	FGameplayTagContainer DodgeTags;
	if (DefaultTag)
	{
		DodgeTags.AddTag(DefaultTag->AbilityDodgeTag);
	}
	if (PlayerCharacter && PlayerCharacter->IsActionable() && PlayerCharacter->IsAlive() && bActionControllable)
	{
		PlayerCharacter->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(DodgeTags);
	}
}

void ARebirthPlayerController::Interact()
{
	//TODO:需要判断当前的游戏模式
	if (CurrentMode == EGameModeType::Free)
	{
		ARebirthCombatPC* PC = Cast<ARebirthCombatPC>(GetCharacter());
		if (PC)
		{
			PC->InteractionComponent->InteractWithInteractingActor();
		}
	}
	else if(CurrentMode == EGameModeType::Director)
	{
		PushForwardInteraction();
	}
	else if (CurrentMode == EGameModeType::Level)
	{
		PushForwardLevel();
	}
}

void ARebirthPlayerController::SearchTarget()
{
	if (!Target)
	{
		FindTarget(0);
	}
	else
	{
		ARebirthCombatNPC* NPC = Cast<ARebirthCombatNPC>(Target);
		if (NPC)
		{
			NPC->RemoveSelfTarget();
			Target = nullptr;
		}
	}
}

void ARebirthPlayerController::SearchTargetX(float Value)
{
	if (!Target || (Value <3 && Value>-3))
	{
		return;
	}
	if (Value > 1)
	{
		Value = 1;
	}
	if (Value < -1)
	{
		Value = -1;
	}
	FindTarget(Value);
}
