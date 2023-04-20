// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ritmo.h"
#include "GameFramework/Actor.h"
#include "Instrumento.generated.h"
class UStaticMesh;
class UStaticMeshComponent;
class USphereComponent;
class UAudioComponent;
class USoundCue;

UCLASS()
class JUEGOMUSICA_API AInstrumento : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInstrumento();
	UPROPERTY(EditAnywhere)
		int id_instrumento;
	UPROPERTY(EditAnywhere, Category = "Parametros")
	float velocidad;

	//Verifica si el instrumento elegido es el correcto en la secuancia
	bool bEsCorrecto = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* bomboSoundBase; //sonido para el Bombo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* hihatSoundBase; //sonido para el Hihat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* cajaSoundBase; //sonido para la caja
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* tom1SoundBase; //sonido para el tom1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* tom2SoundBase; //sonido para el tom2
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* platilloSoundBase; //sonido para el platillo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* rideSoundBase; //sonido para el BrideSound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* sonidoPerder; //sonido para el BrideSound

	UPROPERTY()
	class AAdministradorDeInstrumentos* AdministradorInstrumentos;

	ARitmo * ritmo;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UStaticMeshComponent* MallaInstrumento; // Malla donde se asigna el instrumento 3D cargado
	UStaticMesh* Bombo; //Malla para el Bombo 3d
	UStaticMesh* Hi_hat; //Malla para el Hi-hat 3d
	UStaticMesh* Caja; //Malla para la Caja 3d
	UStaticMesh* Tom1;  //Malla para el Tom1 3d
	UStaticMesh* Tom2;  //Malla para el Tom2 3d
	UStaticMesh* Platillo;  //Malla para el Platillo 3d
	UStaticMesh* Ride;  //Malla para el Ride 3d

	UPROPERTY(EditAnywhere, Category = "Parametros")
	USphereComponent* Colision; // Crea la esfera de colision para los instrumentos

	//arreglo para guardar los instrumentos que se recogeran al unisono
	TArray<int32> instrumentosUnisono;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Caer(float DeltaTime);

	void ElegirMallaInstrumento();

	bool seDestruye = false;

	FString nombre;

	UFUNCTION(BlueprintCallable)
	int getIdInstrumento();

	UFUNCTION()
	void inicializar(int idInstrumento, float VelocidadValor);

	UFUNCTION() // metodo que se llama cuando choca con el jugador
	void OverlapJugador(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere) 
	TSubclassOf<UUserWidget> TextoError1;

	UPROPERTY(EditAnywhere) 
	TSubclassOf<UUserWidget> TextoError2;

	UPROPERTY(EditAnywhere) 
	TSubclassOf<UUserWidget> TextoCorrecto;

	UPROPERTY(EditAnywhere) 
	TSubclassOf<UUserWidget> TextoIncorrecto;

	UUserWidget* PresentarTextosInstance;

private:

	UPROPERTY(EditAnywhere, Category = "Efectos")
	class UParticleSystem* HitParticles; 
};
