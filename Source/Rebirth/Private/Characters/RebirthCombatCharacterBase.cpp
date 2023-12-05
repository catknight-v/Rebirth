// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RebirthCombatCharacterBase.h"
#include "Rebirth/RebirthGameInstance.h"
#include "Rebirth/RebirthAssetManager.h"
#include "Abilities/RebirthGameplayAbility.h"
#include "Items/Item.h"
#include "Rebirth/DefaultTag.h"

// Sets default values
ARebirthCombatCharacterBase::ARebirthCombatCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Ability
	AbilitySystemComponent = CreateDefaultSubobject<URebirthAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<URebirthAttributeSet>(TEXT("AttributeSet"));
	bAbilitiesInitialized = false;

	//Movement
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	bActionable = true;
	bDead = false;
	//GetCharacterMovement()->DisableMovement
}

UAbilitySystemComponent* ARebirthCombatCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool ARebirthCombatCharacterBase::IsActionable()
{
	return bActionable != 0;
}

void ARebirthCombatCharacterBase::SetActionable(bool bCharacterActionable)
{
	if (!bCharacterActionable)
	{
		bActionable = 0;
	}
	else
	{
		bActionable = 1;
	}
	/*if (bCharacterActionable)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
	else
	{
		GetCharacterMovement()->DisableMovement();
	}*/
}

void ARebirthCombatCharacterBase::LoadDefaultItems()
{
	URebirthGameInstance* GameInstance = Cast<URebirthGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		TSubclassOf<ARebirthCombatCharacterBase> ThisClass = GetClass();
		URebirthAssetManager& AssetManager = URebirthAssetManager::Get();
		UCombatCharacterDefaultInventory* DefaultInventory = GameInstance->GetDefaultInventory();
		if (DefaultInventory)
		{
			FDefaultInventory* Inventory = DefaultInventory->Data.Find(ThisClass);
			if (Inventory)
			{
				for (const TPair<FPrimaryAssetId, FItemData>& Pair : Inventory->Data)
				{
					UItem* Item = AssetManager.ForceLoadItem(Pair.Key);
					Knapsack.AddInventoryItem(Item, Pair.Value.ItemCount);
				}
			}
		}
	}
}

void ARebirthCombatCharacterBase::InitAbilities()
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	for (TPair<UItem*, FItemData> Pair : Knapsack.InventoryData)
	{
		for (TSubclassOf<UGameplayAbility> Ability : Pair.Key->GrantedAbilities)
		{
			if (HasAuthority() && Ability)
			{
				AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability));
			}
		}
	}
	bAbilitiesInitialized = true;
}

void ARebirthCombatCharacterBase::ActivateInitAbilities()
{
	if (AbilitySystemComponent && bAbilitiesInitialized)
	{
		URebirthGameInstance* GameInstance = Cast<URebirthGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			UDefaultTag* DefaultTag = GameInstance->GetDefaultTag();
			if (DefaultTag)
			{
				FGameplayTagContainer InitTags;
				InitTags.AddTag(DefaultTag->AbilityInitTag);
				AbilitySystemComponent->TryActivateAbilitiesByTag(InitTags);
			}
		}
	}
}

void ARebirthCombatCharacterBase::CombatCharacterInit()
{
	LoadDefaultItems();
	InitAbilities();
	ActivateInitAbilities();
}

void ARebirthCombatCharacterBase::CombatReset()
{
	bDead = false;
	SetActionable(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ActivateInitAbilities();
}

void ARebirthCombatCharacterBase::FaceToInstantly(FVector Location)
{
	FVector Direction = Location - GetActorLocation();
	FRotator Rotator = Direction.Rotation();
	Rotator.Pitch = 0;
	SetActorRotation(Rotator);
}

// Called when the game starts or when spawned
void ARebirthCombatCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	CombatCharacterInit();
	ActivateInitAbilities();
}

bool ARebirthCombatCharacterBase::IsAlive() const
{
	return bDead == 0;
}

float ARebirthCombatCharacterBase::GetHealth() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetHealth();
	}
	return 1.0f;
}

float ARebirthCombatCharacterBase::GetMaxHealth() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetMaxHealth();
	}
	return 1.f;
}

float ARebirthCombatCharacterBase::GetEnergy() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetEnergy();
	}
	return 0.f;
}

float ARebirthCombatCharacterBase::GetMaxEnergy() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetMaxEnergy();
	}
	return 0.f;
}

float ARebirthCombatCharacterBase::GetMoveSpeed() const
{
	if (AttributeSet)
	{
		return AttributeSet->GetMoveSpeed();
	}
	return 0.f;
}

void ARebirthCombatCharacterBase::HandleDamage(float DamageAmount, const FHitResult& HitInfo, const FGameplayTagContainer& DamageTags, ARebirthCombatCharacterBase* InstigatorCharacter, AActor* DamageCauser)
{
	if (!bDead)
	{
		if (FMath::IsNearlyZero(GetHealth()))
		{
			HandleDeath(DamageAmount, HitInfo, DamageTags, InstigatorCharacter, DamageCauser);
			OnDeath(DamageAmount, HitInfo, DamageTags, InstigatorCharacter, DamageCauser);
		}
		else
		{
			OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorCharacter, DamageCauser);
		}
	}
}

void ARebirthCombatCharacterBase::HandleDeath(float DamageAmount, const FHitResult& HitInfo, const FGameplayTagContainer& DamageTags, ARebirthCombatCharacterBase* InstigatorCharacter, AActor* DamageCauser)
{
	bDead = true;
	SetActionable(false);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARebirthCombatCharacterBase::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	OnHealthChanged(DeltaValue, EventTags);
}

void ARebirthCombatCharacterBase::HandleEnergyChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	OnEnergyChanged(DeltaValue, EventTags);
}

void ARebirthCombatCharacterBase::HandleMoveSpeedChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
	OnMoveSpeedChanged(DeltaValue, EventTags);
}
