// Fill out your copyright notice in the Description page of Project Settings.


#include "Audiencia.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimSequence.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AAudiencia::AAudiencia()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Audiencia = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Malla"));
	RootComponent = Audiencia;

	
	//RootComponent = Capsula;
	
	//Audiencia->SetupAttachment(Capsula);

	//////////////////////////////////////////////////////////////////////////////////////////
	//Cargamos la malla y la Animacion del Personaje Cheering
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PersonajeCheeringMesh(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeCheering/Cheering.Cheering"));

	if (PersonajeCheeringMesh.Succeeded()) {
		PersonajeCheering = PersonajeCheeringMesh.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimCheering(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeCheering/AS_Cheering.AS_Cheering"));
	CheeringAnim = AnimCheering.Object;

	///////////////////////////////////////////////////////////////////////////////////////////
	//Cargamos la malla y la Animacion del Personaje GuitarPlaying
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PersonajeGuitarPlayingMesh(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeGuitarPlaying/Guitar_Playing.Guitar_Playing"));

	if (PersonajeGuitarPlayingMesh.Succeeded()) {
		PersonajeGuitarPlaying = PersonajeGuitarPlayingMesh.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimGuitarPlaying(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeGuitarPlaying/AS_GuitarPlaying.AS_GuitarPlaying"));
	GuitarPlayingAnim = AnimGuitarPlaying.Object;

	///////////////////////////////////////////////////////////////////////////////////////////
	//Cargamos la malla y la Animacion del Personaje Shuffling
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PersonajeShufflingMesh(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeShuffling/Shuffling.Shuffling"));

	if (PersonajeShufflingMesh.Succeeded()) {
		PersonajeShuffling = PersonajeShufflingMesh.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimShuffling(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeShuffling/AS_Shuffling.AS_Shuffling"));
	ShufflingAnim = AnimShuffling.Object;

	///////////////////////////////////////////////////////////////////////////////////////////
	//Cargamos la malla y la Animacion del Personaje Victory
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PersonajeVictoryMesh(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeVictory/Victory.Victory"));

	if (PersonajeVictoryMesh.Succeeded()) {
		PersonajeVictory = PersonajeVictoryMesh.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimVictory(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeVictory/AS_Victory.AS_Victory"));
	VictoryAnim = AnimVictory.Object;

	///////////////////////////////////////////////////////////////////////////////////////////
	//Cargamos la malla y la Animacion del Personaje Clap
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PersonajeClapMesh(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeClap/Clap.Clap"));

	if (PersonajeClapMesh.Succeeded()) {
		PersonajeClap = PersonajeClapMesh.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimClap(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeClap/AS_Clap.AS_Clap"));
	ClapAnim = AnimClap.Object;

	///////////////////////////////////////////////////////////////////////////////////////////
	//Cargamos la malla y la Animacion del Personaje PersonajeJoyfull
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PersonajeJoyfullMesh(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeJoyfull/Joyfull.Joyfull"));

	if (PersonajeJoyfullMesh.Succeeded()) {
		PersonajeJoyfull = PersonajeJoyfullMesh.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimJoyfull(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeJoyfull/AS_Joyfull.AS_Joyfull"));
	JoyfullAnim = AnimJoyfull.Object;

	///////////////////////////////////////////////////////////////////////////////////////////
	//Cargamos la malla y la Animacion del Personaje PersonajeJump
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PersonajeJumpMesh(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeJump/Jump.Jump"));

	if (PersonajeJumpMesh.Succeeded()) {
		PersonajeJump = PersonajeJumpMesh.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimJump(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajeJump/AS_Jump.AS_Jump"));
	JumpAnim = AnimJump.Object;

	///////////////////////////////////////////////////////////////////////////////////////////
	//Cargamos la malla y la Animacion del Personaje PersonajePlayingViolin
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PersonajePlayingViolinMesh(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajePlayingViolin/PlayingViolin.PlayingViolin"));

	if (PersonajePlayingViolinMesh.Succeeded()) {
		PersonajePlayingViolin = PersonajePlayingViolinMesh.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimPlayingViolin(TEXT("/Game/ThirdPersonCPP/Audiencia/PersonajePlayingViolin/AS_PlayingViolin.AS_PlayingViolin"));
	PlayingViolinAnim = AnimPlayingViolin.Object;

	Capsula = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsula"));
	Capsula->SetupAttachment(RootComponent);
	Capsula->SetCapsuleHalfHeight(24.f);
	Capsula->SetCapsuleRadius(8.f);
}

// Called when the game starts or when spawned
void AAudiencia::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAudiencia::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Escoge un numero aleatorio para crear un diferente personaje de audiencia
void AAudiencia::NumeroAleatorioPersonajeAudiencia()
{
	int32 Eleccion = FMath::RandRange(1,8);
	switch (Eleccion)
	{
	case 1:
		ElegirMallaPersonajeAudiencia(PersonajeCheering, CheeringAnim);
		break;
	case 2:
		ElegirMallaPersonajeAudiencia(PersonajeGuitarPlaying, GuitarPlayingAnim);
		break;
	case 3:
		ElegirMallaPersonajeAudiencia(PersonajeShuffling, ShufflingAnim);
		break;
	case 4:
		ElegirMallaPersonajeAudiencia(PersonajeVictory, VictoryAnim);
		break;
	case 5:
		ElegirMallaPersonajeAudiencia(PersonajeClap, ClapAnim);
		break;
	case 6:
		ElegirMallaPersonajeAudiencia(PersonajeJoyfull, JoyfullAnim);
		break;
	case 7:
		ElegirMallaPersonajeAudiencia(PersonajeJump, JumpAnim);
		break;
	case 8:
		ElegirMallaPersonajeAudiencia(PersonajePlayingViolin, PlayingViolinAnim);
		break;
	default:
		break;
	}
}

void AAudiencia::ElegirMallaPersonajeAudiencia(USkeletalMesh* MallaElegida, UAnimSequence* Animacion)
{
	if (Audiencia && MallaElegida)
	{
		Audiencia->SetSkeletalMesh(MallaElegida);
		Audiencia->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	}
	
	if (Animacion)
	{
		float VelocidadAnimacion = FMath::RandRange(0.5f, 1.f);
		bool Pausa = FMath::RandBool();
		Audiencia->PlayAnimation(Animacion,Pausa);
		Audiencia->SetPlayRate(VelocidadAnimacion);
	}

}



