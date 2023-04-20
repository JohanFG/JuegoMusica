// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AdministradorDeInstrumentos.generated.h"

class AInstrumento;

UCLASS()
class JUEGOMUSICA_API AAdministradorDeInstrumentos : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdministradorDeInstrumentos();
	UPROPERTY(EditDefaultsOnly, Category = Instrumento)
		TSubclassOf<AInstrumento> InstrumentoClass;
		
	UPROPERTY(BlueprintReadWrite)
		int32 id_instrumento = FMath::RandRange(1, 4);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int dificultad;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle GenerarInstrumentoTimerHandle; // variable que administra el tiempo

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void CrearInstrumento();

	UFUNCTION()
	void Desbloquear();

	UFUNCTION()
	void ApagarGenerador();

	UFUNCTION()
	void ObtenerRandomInstrumentos(int& dif); 
};
