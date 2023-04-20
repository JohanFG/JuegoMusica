// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "CameraScene.generated.h"


UCLASS()
class JUEGOMUSICA_API ACameraScene : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraScene();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ProcessMovementTimeline(float Value);

	UFUNCTION()
	void OnEndMovementTimeline();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spline", meta=(AllowPrivateAccess = "true"))
	class USplineComponent* SplineComp;

	UPROPERTY(EditAnywhere)
    class UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spline")
	class UCurveFloat* MovementCurve;

	void MoverCamara(FVector Location);

	void MoverCamaraPrimerPlano(FVector Location);

	void MoverCamaraPrimerPlanoGanador(FVector Location);

private:
	
	FTimeline MovementTimeline;

	UPROPERTY()
	class AJuegoMusicaCharacter* PersonajeJuego;

	// FTimerHandle MoveCameraTimerHandle;

	// float MoveCameraRate = 2.f;
};
