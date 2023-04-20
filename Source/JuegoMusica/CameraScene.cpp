// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraScene.h"
#include "Camera/CameraComponent.h"
#include "JuegoMusicaCharacter.h"
#include "Components/SplineComponent.h"

// Sets default values
ACameraScene::ACameraScene()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	RootComponent = SplineComp;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera COmponent"));
	CameraComp->SetupAttachment(SplineComp);
}

// Called when the game starts or when spawned
void ACameraScene::BeginPlay()
{
	Super::BeginPlay();
	
	FOnTimelineFloat ProgressFunction;
	ProgressFunction.BindUFunction(this, TEXT("ProcessMovementTimeline"));
	MovementTimeline.AddInterpFloat(MovementCurve, ProgressFunction);

	FOnTimelineEvent OnTimelineFinishedFunction;
	OnTimelineFinishedFunction.BindUFunction(this, TEXT("OnEndMovementTimeline"));
	MovementTimeline.SetTimelineFinishedFunc(OnTimelineFinishedFunction);

	MovementTimeline.SetTimelineLengthMode(TL_LastKeyFrame);
	MovementTimeline.Play();
}

// Called every frame
void ACameraScene::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementTimeline.IsPlaying())
	{
		MovementTimeline.TickTimeline(DeltaTime);
	}
}

void ACameraScene::MoverCamara(FVector Location)
{
	CameraComp->SetWorldLocation(Location + FVector(-800, -0, 110));
}

void ACameraScene::MoverCamaraPrimerPlano(FVector Location)
{
	CameraComp->SetWorldLocation(Location + FVector(-200, -0, 10));
}


void ACameraScene::MoverCamaraPrimerPlanoGanador(FVector Location)
{
	CameraComp->SetWorldLocation(Location + FVector(-0, -0, 0));
}

void ACameraScene::ProcessMovementTimeline(float Value)
{
	const float SplineLength = SplineComp->GetSplineLength();
	
	FVector CurrentSplineLocation = SplineComp->GetLocationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);
	FRotator CurrentSplineRotation = SplineComp->GetRotationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);

	CameraComp->SetWorldLocationAndRotation(CurrentSplineLocation, CurrentSplineRotation);
}

void ACameraScene::OnEndMovementTimeline()
{

}

