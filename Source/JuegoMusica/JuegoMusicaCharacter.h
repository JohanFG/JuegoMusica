// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JuegoMusicaCharacter.generated.h"

UCLASS(config=Game)
class AJuegoMusicaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AJuegoMusicaCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = Instrumento)
	TSubclassOf<class AAudiencia> AudienciaClass;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int vidas = 3;

	UFUNCTION()
	void perderVida();

	UFUNCTION()
	void MoverPersonajeGanador();

	UFUNCTION()
	void PlayCameraShake();

	UFUNCTION()
	void PlayCameraInstrumentShake();

	UPROPERTY()
	bool CambioCamara = false;

protected:

	/** Called for side to side input */
	void MoveRight(float AxisValue);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;

private:

	// Puntero utilizado para generar los efectos agitar la camara
	UPROPERTY(EditAnywhere, Category = "Camara Efecto")
	TSubclassOf <class UCameraShakeBase> HitCameraShakeClass;

	// Puntero utilizado para generar los efectos agitar la camara cuando selecciona un instrumento
	UPROPERTY(EditAnywhere, Category = "Camara Efecto")
	TSubclassOf <class UCameraShakeBase> HitInstrumentShakeClass;

	UFUNCTION()
	void CrearPersonajesAudiencia();

	UFUNCTION()
	void EsperarEntradaCamara();

	UFUNCTION()
	TArray<FVector> GenerarVectoresAleatoriosAudiencia();

	UPROPERTY()
	TArray<FVector> PosicionesAudiencia;

	UPROPERTY()
    class ACameraScene* CameraScene;

	UPROPERTY()
	FTimerHandle MoveCameraTimerHandle;

	UPROPERTY()
	class AAdministradorDeInstrumentos* AdministradorInstrumentos;

};

