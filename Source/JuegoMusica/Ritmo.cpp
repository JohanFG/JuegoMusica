// Fill out your copyright notice in the Description page of Project Settings.


#include "Ritmo.h"
#include "AdministradorDeInstrumentos.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARitmo::ARitmo()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// tom2 --- 1
	// caja --- 2
	// bombo --- 3
	// crash --- 4
	// tom1 --- 5
	// hihat --- 6
	// ride --- 7

	// orden para los instrumentos faciles
	facil1 = {1, 1, 2, 1, 1, 2, 4}; 
	facil2 = {3, 3, 2, 3, 3, 2, 1, 1, 1, 4};
	facil3 = {4, 4, 2, 2, 2, 2, 1, 1, 1, 3, 3, 2};
	facil4 = {2, 2, 2, 1, 1, 1, 3, 3, 1, 1, 3, 4};
	

	//orden para los instrumentos intermedios
	medio1 = {2, 2, 5, 5, 2, 2, 1, 1, 3, 5, 1, 34}; 
	medio2 = {34, 2, 2, 5, 5, 1, 1, 3, 3, 2, 2, 3, 34};
	medio3 = {2, 2, 2, 34, 2, 2, 2, 34, 5, 5, 5, 1, 1, 1, 3, 3, 2}; 
	medio4 = {34, 34, 2, 2, 5, 5, 3, 1, 1, 3, 5, 5, 34}; 
	
	//orden para los instrumentos dificiles
	dificil1 = {34, 7, 27, 5, 5, 37, 7, 27, 1, 1, 34}; 
	dificil2 = {5, 5, 1, 1, 36, 26, 36, 3, 26, 36, 26, 34}; 
	dificil3 = {3, 1, 5, 3, 1, 5, 3, 1, 5, 3, 3, 1, 1, 3, 27, 34}; 
	dificil4 = {34, 2, 2, 2, 2, 5, 5, 3, 3, 34, 26, 6, 36, 36, 27, 27, 34}; 
	
}

// Called when the game starts or when spawned
void ARitmo::BeginPlay()
{
	Super::BeginPlay();

	AsignarRitmo(dificultad, ritmo);

	idInstrumentoActual = secuencia[0];

	tamSecuencia = secuencia.Num();

}

// Called every frame
void ARitmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Hacer unisono: %i"), bHacerUnisono)
}

void ARitmo::AsignarRitmo(int& dif, int& rit)
{
	switch (dif)
	{
	case 1:
		switch (rit)
		{
		case 1:
			secuencia = facil1;
			break;
		
		case 2:
			secuencia = facil2;
			break;
		
		case 3:
			secuencia = facil3;
			break;
		
		case 4:
			secuencia = facil4;
			break;
		
		default:
			break;
		}
		break;

	case 2:
		switch (rit)
		{
		case 1:
			secuencia = medio1;
			break;
		
		case 2:
			secuencia = medio2;
			break;
		
		case 3:
			secuencia = medio3;
			break;
		
		case 4:
			secuencia = medio4;
			break;
		
		default:
			break;
		}
		break;
	
	case 3:
		switch (rit)
		{
		case 1:
			secuencia = dificil1;
			break;
		
		case 2:
			secuencia = dificil2;
			break;
		
		case 3:
			secuencia = dificil3;
			break;
		
		case 4:
			secuencia = dificil4;
			break;
		
		default:
			break;
		}
		break;
	default:
		break;
	}
}

TArray<int32> ARitmo::getInstrumentoActual() {

	if (!bEsUnisono)
	{
		if (idInstrumentoActual > 7)
		{
			int32 ultimo = idInstrumentoActual % 10;
			int32 primero = FMath::FloorToInt(idInstrumentoActual / 10);
			instrumentos = {primero, ultimo};
			bEsUnisono = true;
			UE_LOG(LogTemp, Error, TEXT("%i"), ultimo)
			UE_LOG(LogTemp, Error, TEXT("%i"), primero)
			return instrumentos;	
		}else{
			instrumentos = {idInstrumentoActual};
			return instrumentos;
		}
	}else{
		return instrumentos;
	}
	
}

void ARitmo::ModificarArregloUnisono(int& id){
	
	int32 Index;
	/*for (int32 N : instrumentos) {
		UE_LOG(LogTemp, Warning, TEXT("Instrumento:       %i"), N);
	}*/
	instrumentos.Find(id, Index);
	
	//UE_LOG(LogTemp, Warning, TEXT("Cantidad de instr antes %i"), instrumentos.Num())
	if(Index != -1){
		instrumentos.RemoveAt(Index);
	} else {
		bSeEquivocaUnisono = true;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Index en el array %i"), Index)
	//UE_LOG(LogTemp, Warning, TEXT("Cantidad de instr despues %i"), instrumentos.Num())
	j++;
	
}

void ARitmo::VerificarRitmoCorrecto(){

	/*for (bool V : VerificarSecuenciaRitmo)
	{
		UE_LOG(LogTemp, Warning, TEXT("     %i :"), V)
	}*/

	if (VerificarSecuenciaRitmo.Contains(false))
	{
		UE_LOG(LogTemp, Warning, TEXT("contiene falsos"))
		PresentarInstrumentosInstance = CreateWidget<UUserWidget>(GetWorld(), PresentarInstrumentos);
		if (PresentarInstrumentosInstance)
		{
			PresentarInstrumentosInstance->AddToViewport();
			UGameplayStatics::SpawnSound2D(this, sonidoCulminar);
		}

	}else{
		UE_LOG(LogTemp, Warning, TEXT("TODO OK"))
		bTodoEsCorrecto = true;
		UGameplayStatics::SpawnSound2D(this, sonidoGanar);
	}
	
}


int ARitmo::getDificultadActual() {

	return dificultad;
}

int ARitmo::getInstrumentoSiguiente()
{
	if (secuencia.IsValidIndex(i + 1)) {
		return secuencia[i + 1];
	}
	return 0;
}

void ARitmo::siguienteInstrumento()
{
	i++;
	if (secuencia.IsValidIndex(i)) {
		bEsUnisono = false;
		idInstrumentoActual = secuencia[i];
	}
	bHacerUnisono = false;
	//bActivadoUnisono = false;
}

TArray<bool> ARitmo::getVerificarSecuenciaRitmo()
{
	return VerificarSecuenciaRitmo;
}

int32 ARitmo::getTamSecuencia()
{
	return tamSecuencia;
}

