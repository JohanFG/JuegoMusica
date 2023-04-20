// Fill out your copyright notice in the Description page of Project Settings.


#include "AdministradorDeInstrumentos.h"
#include "Kismet/GameplayStatics.h"
#include "Instrumento.h"
#include "Ritmo.h"
#include "TimerManager.h"
// Sets default values
AAdministradorDeInstrumentos::AAdministradorDeInstrumentos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AAdministradorDeInstrumentos::BeginPlay()
{
	Super::BeginPlay();

	//ObtenerRandomInstrumentos(dificultad);
}

// Called every frame
void AAdministradorDeInstrumentos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAdministradorDeInstrumentos::ObtenerRandomInstrumentos(int& dif){
	switch (dif)
	{
	case 1:
		id_instrumento = FMath::RandRange(1, 4);
		break;

	case 2:
		id_instrumento = FMath::RandRange(1, 5);
		break;

	case 3:
		id_instrumento = FMath::RandRange(1, 7);
		break;
		
	default:
		break;
	}
}

void AAdministradorDeInstrumentos::CrearInstrumento() {

	float variacionY = FMath::RandRange(-500.f, 500.f);
	FTransform SpawnTransform(FRotator(0.f, 0.f, 0.f),GetActorLocation()+FVector(0.f, variacionY,0.f));
	auto InstrumentoNuevo = Cast<AInstrumento>
	(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, InstrumentoClass, SpawnTransform));  //Spawnea un instrumento en el escenario
	
	if (InstrumentoNuevo != nullptr) { // cuando se desboquea
		
			InstrumentoNuevo->inicializar(id_instrumento, 400); // se llaman estos parametros del instrumento antes de su constructor
			UGameplayStatics::FinishSpawningActor(InstrumentoNuevo, SpawnTransform); // se termina de llamar al instrumento y se crea
			/*id_instrumento = ObtenerRandomInstrumentos(dificultad); // enseguida luego de crearse, se define el id del instrumento siguiente y la posicion donde aparece, ambos aleatoriamente*/
			ObtenerRandomInstrumentos(dificultad);
	}
}

// desbloquea el Administrador de instrumentos para que empiece a generarlos, metodo llamado desde AJuegoMusicaCharacter despues que paso el tiempo de la entrada
void AAdministradorDeInstrumentos::Desbloquear() { 

	GetWorldTimerManager().SetTimer(GenerarInstrumentoTimerHandle, this, &AAdministradorDeInstrumentos::CrearInstrumento, 2.f, true, 0.f);

}


void AAdministradorDeInstrumentos::ApagarGenerador()
{
	GetWorldTimerManager().ClearTimer(GenerarInstrumentoTimerHandle);
}