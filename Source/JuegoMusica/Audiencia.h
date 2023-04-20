// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Audiencia.generated.h"

class USkeletalMesh;
class UAnimSequence;

UCLASS()
class JUEGOMUSICA_API AAudiencia : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudiencia();
	
	UFUNCTION()
	void NumeroAleatorioPersonajeAudiencia();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//Capsula de Colision 
	UPROPERTY(EditAnywhere, Category = "Parametros")
	class UCapsuleComponent* Capsula;

	//Componente Unico para las diferentes SkeletalMesh
	USkeletalMeshComponent* Audiencia;

	//SkeletalMesh para cada personaje de la audiencia
	USkeletalMesh* PersonajeCheering;
	USkeletalMesh* PersonajeGuitarPlaying;
	USkeletalMesh* PersonajeShuffling;
	USkeletalMesh* PersonajeVictory;
	USkeletalMesh* PersonajeClap;
	USkeletalMesh* PersonajeJoyfull;
	USkeletalMesh* PersonajeJump;
	USkeletalMesh* PersonajePlayingViolin;

	//Animaciones que los personajes realizan
	UAnimSequence* CheeringAnim;
	UAnimSequence* GuitarPlayingAnim;
	UAnimSequence* ShufflingAnim;
	UAnimSequence* VictoryAnim;
	UAnimSequence* ClapAnim;
	UAnimSequence* JoyfullAnim;
	UAnimSequence* JumpAnim;
	UAnimSequence* PlayingViolinAnim;

	UFUNCTION()
	void ElegirMallaPersonajeAudiencia (USkeletalMesh* MallaElegida, UAnimSequence* Animacion);

	
};
