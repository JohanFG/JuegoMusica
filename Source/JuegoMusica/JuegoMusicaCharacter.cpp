// Copyright Epic Games, Inc. All Rights Reserved.

#include "JuegoMusicaCharacter.h"
#include "AdministradorDeInstrumentos.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "CameraScene.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Audiencia.h"

//////////////////////////////////////////////////////////////////////////
// AJuegoMusicaCharacter
void AJuegoMusicaCharacter::BeginPlay() 
{
	Super::BeginPlay();

	CrearPersonajesAudiencia();

	GetWorldTimerManager().SetTimer(MoveCameraTimerHandle, this, &AJuegoMusicaCharacter::EsperarEntradaCamara , 3.f, false);
	CameraScene = Cast<ACameraScene>(UGameplayStatics::GetActorOfClass(this, ACameraScene::StaticClass()));

	AdministradorInstrumentos = Cast<AAdministradorDeInstrumentos>(UGameplayStatics::GetActorOfClass(this, AAdministradorDeInstrumentos::StaticClass()));
	//GetWorld()->SpawnActor(AAudiencia::StaticClass());

	
}
	

void AJuegoMusicaCharacter::Tick (float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Location = GetActorLocation();

	if (CambioCamara){
		if (CameraScene)
		{
			CameraScene->MoverCamara(Location);
		}
	}

	if(vidas<1){
		AdministradorInstrumentos->ApagarGenerador();
		if (CameraScene)
		{
			CameraScene->MoverCamaraPrimerPlano(Location);
		}
	}
}

AJuegoMusicaCharacter::AJuegoMusicaCharacter()
{

	PosicionesAudiencia = GenerarVectoresAleatoriosAudiencia();

}

//////////////////////////////////////////////////////////////////////////
// Input

void AJuegoMusicaCharacter::EsperarEntradaCamara()
{
	CambioCamara = true;
	if (AdministradorInstrumentos)
	{
		AdministradorInstrumentos->Desbloquear();
	}
	
}

void AJuegoMusicaCharacter::MoverPersonajeGanador()
{
	FVector Location = FVector(249, -17, 500);
	this->SetActorLocation(Location);

	if (CameraScene)
	{
		CameraScene->MoverCamaraPrimerPlanoGanador(Location);
	}
	
	
}

void AJuegoMusicaCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveRight", this, &AJuegoMusicaCharacter::MoveRight);


	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AJuegoMusicaCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AJuegoMusicaCharacter::TouchStopped);

}


void AJuegoMusicaCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AJuegoMusicaCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}


void AJuegoMusicaCharacter::perderVida()
{
	vidas--;
}

//Genera el movimiento de izquierda a derecha
void AJuegoMusicaCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

//Genera el movimiento de la camara al chocar con el limite del escenario
void AJuegoMusicaCharacter::PlayCameraShake()
{
	if(HitCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}
}

//Genera el movimiento de la camara al coger un instrumento
void AJuegoMusicaCharacter::PlayCameraInstrumentShake()
{
	if(HitInstrumentShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitInstrumentShakeClass);
	}
}


//Metodo que guarda vectores aleatorios con un rango de separacion para que la Audiencia, no choquen sus mallas
TArray<FVector> AJuegoMusicaCharacter::GenerarVectoresAleatoriosAudiencia()
{
	TArray<FVector> PosicionesPosibles;
	bool bMismaPosicion = false;
	while (PosicionesPosibles.Num() < 100)
	{
		FVector Posicion = UKismetMathLibrary::RandomPointInBoundingBox(FVector(-1250.f, -20.f, 120.f), FVector(500.f, 700.f, 0.f));
		for (FVector Iteraciones : PosicionesPosibles)
		{
			//FVector::PointsAreNear(Iteraciones, Posicion, 20.f)
			if(FVector::PointsAreNear(Iteraciones, Posicion, 30.f))
			{
				bMismaPosicion = true;
				break;
			}
		}
		if (!bMismaPosicion)
		{
			PosicionesPosibles.Add(Posicion);
		} else
		{
			bMismaPosicion = false;
		}
	}
	return PosicionesPosibles;
}


//Genera los personajes de la Audiencia aleatoriamente
void AJuegoMusicaCharacter::CrearPersonajesAudiencia()
{
	
	for (FVector Vectores : PosicionesAudiencia)
	{
		FTransform SpawnTransform(FRotator(0.f, 0.f, 0.f), Vectores);
		AAudiencia* PersonajeNuevo = Cast<AAudiencia> (UGameplayStatics::BeginDeferredActorSpawnFromClass(this, AudienciaClass, SpawnTransform));	
		PersonajeNuevo->NumeroAleatorioPersonajeAudiencia();
		UGameplayStatics::FinishSpawningActor(PersonajeNuevo, SpawnTransform);
	}
}
	
	
