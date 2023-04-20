// Fill out your copyright notice in the Description page of Project Settings.


#include "BloquesLimitadores.h"
#include "Components/BoxComponent.h"
#include "JuegoMusicaCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABloquesLimitadores::ABloquesLimitadores()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CajaLimitante = CreateDefaultSubobject<UBoxComponent>(TEXT("Caja"));
	
}

// Called when the game starts or when spawned
void ABloquesLimitadores::BeginPlay()
{
	Super::BeginPlay();

	CajaLimitante->OnComponentHit.AddDynamic(this, &ABloquesLimitadores::OnHit);

}

// Called every frame
void ABloquesLimitadores::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABloquesLimitadores::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Personaje = Cast<AJuegoMusicaCharacter>(OtherActor);
	
	if(Personaje)
	{
		Personaje->PlayCameraShake();
	}
}

