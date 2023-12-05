// Fill out your copyright notice in the Description page of Project Settings.


#include "TopSideView/TopSideViewTargetActor.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraTypes.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ATopSideViewTargetActor::ATopSideViewTargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetupAttachment(GetRootComponent());

	// 
	FVector CapsuleComponentLocation(0, 0, TopSideViewInfo.CameraDistance / 2);
	CapsuleComponent->SetRelativeLocation(CapsuleComponentLocation);
	CapsuleComponent->SetCapsuleHalfHeight(TopSideViewInfo.CameraDistance / 2);
	CapsuleComponent->SetCapsuleRadius(5.f);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	CapsuleComponent->SetGenerateOverlapEvents(true);
}

void ATopSideViewTargetActor::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	FVector ViewTargetLocation = GetActorLocation();
	float TopDownRadians = FMath::DegreesToRadians(TopSideViewInfo.CurrentRate);
	FVector LookDirection = FVector(0, FMath::Cos(TopDownRadians), -FMath::Sin(TopDownRadians));
	FVector NewLocation = -LookDirection * TopSideViewInfo.CameraDistance + ViewTargetLocation;
	//NewLocation.Z += ViewInfo.MeshDistance;
	FRotator NewRotation = LookDirection.Rotation();
	OutResult.Location = NewLocation;
	OutResult.Rotation = NewRotation;

	//每次计算自身Actor的Rotation 使其朝向摄像机

	FVector ActorDirection = FVector(0, FMath::Sin(TopDownRadians), FMath::Cos(TopDownRadians));
	FRotator ActorRotation = ActorDirection.Rotation();
	SetActorRotation(ActorRotation);

}

void ATopSideViewTargetActor::SetViewInfo(const FTopSideViewInfo& ViewInfo)
{
	TopSideViewInfo = ViewInfo;
	//UStaticMeshComponent::GetMaterial
	//UMaterialInterface* MaterialInterface;
	//MaterialInterface->SetScalarParameterValue
	//UMaterialInstanceDynamic
}
