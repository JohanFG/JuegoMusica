// Fill out your copyright notice in the Description page of Project Settings.


#include "Instrumento.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Ritmo.h"
#include "Blueprint/UserWidget.h"
#include "AdministradorDeInstrumentos.h"
#include "JuegoMusicaCharacter.h"
// Sets default values
AInstrumento::AInstrumento()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MallaInstrumento = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
	MallaInstrumento->SetMobility(EComponentMobility::Movable);
	MallaInstrumento->SetWorldScale3D(0.25f*FVector(1.f,1.f,1.f));
	RootComponent = MallaInstrumento;

	ritmo = Cast<ARitmo>(UGameplayStatics::GetActorOfClass(this, ARitmo::StaticClass()));
	


	// Carga la malla 3D del tom1
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Tom1Mesh(TEXT("/Game/Assets3D/Tom1.Tom1"));
	if (Tom1Mesh.Succeeded()) {
		Tom1 = Tom1Mesh.Object;
	}



	// Carga la malla 3D del tom2
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Tom2Mesh(TEXT("/Game/Assets3D/Tom2.Tom2"));
	if (Tom2Mesh.Succeeded()) {
		Tom2 = Tom2Mesh.Object;
	}


	// Carga la malla 3D de la caja
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CajaMesh(TEXT("/Game/Assets3D/Caja.Caja"));
	if (CajaMesh.Succeeded()) {
		Caja = CajaMesh.Object;
	}



	// Carga la malla 3D del bombo
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BomboMesh(TEXT("/Game/Assets3D/Bombo.Bombo"));
	if (BomboMesh.Succeeded()) {
		Bombo = BomboMesh.Object;
	}



	// Carga la malla 3D del Hi-hat
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Hi_HatMesh(TEXT("/Game/Assets3D/Hihat.Hihat"));
	if (Hi_HatMesh.Succeeded()) {
		Hi_hat = Hi_HatMesh.Object;
	}


	// Carga la malla 3D del platillo
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlatilloMesh(TEXT("/Game/Assets3D/Platillo.Platillo"));
	if (PlatilloMesh.Succeeded()) {
		Platillo = PlatilloMesh.Object;
	}



	// Carga la malla 3D del Ride
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RideMesh(TEXT("/Game/Assets3D/Ride.Ride"));
	if (RideMesh.Succeeded()) {
		Ride = RideMesh.Object;
	}



	// Personaliza la esfera de detecciond e colision
	Colision = CreateDefaultSubobject<USphereComponent>(TEXT("EsferaDeColision"));
	Colision->SetupAttachment(RootComponent);
	Colision->SetSphereRadius(50.f);

	Colision->OnComponentBeginOverlap.AddDynamic(this, &AInstrumento::OverlapJugador);
}

void AInstrumento::inicializar(int idInstrumento, float VelocidadValor) {
	this->id_instrumento = idInstrumento;
	this->velocidad = VelocidadValor;

}

// Called when the game starts or when spawned
void AInstrumento::BeginPlay()
{
	Super::BeginPlay();

	AdministradorInstrumentos = Cast<AAdministradorDeInstrumentos>(UGameplayStatics::GetActorOfClass(this, AAdministradorDeInstrumentos::StaticClass()));
	// Eligue la malla del instrumento
	ElegirMallaInstrumento();
	
}

// Called every frame
void AInstrumento::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Caer(DeltaTime);
	FRotator rotNueva = GetActorRotation();
	rotNueva +=  FRotator(0.f, DeltaTime * 100.f,0.f);
	SetActorRotation(rotNueva);
	// if (GetActorLocation().Z < 100.f) {
	// 	seDestruye = true;
	// 	Destroy();
	// }
}

void AInstrumento::Caer(float DeltaTime) {
	// mueve al objeto en direccion vertical
	FVector Posicion = GetActorLocation();
	FVector Direccion = FVector(0.f, 0.f, -1.f);
	Posicion += Direccion * velocidad * DeltaTime;
	SetActorLocation(Posicion);
}

void AInstrumento::ElegirMallaInstrumento() {
	//elige el instrumento segun el id_instrumento y su respectivo sonido
	if (id_instrumento == 1) {

		MallaInstrumento->SetStaticMesh(Tom2);
		
		nombre = "Tom2";
	}
	if (id_instrumento == 2) {

		MallaInstrumento->SetStaticMesh(Caja);
		
		nombre = "Caja";
		
	}
	if (id_instrumento == 3) {

		MallaInstrumento->SetStaticMesh(Bombo);
		
		nombre = "Bombo";
		
	}
	if (id_instrumento == 4) {

		MallaInstrumento->SetStaticMesh(Platillo);
		
		nombre = "Platillo";
		
	}
	if (id_instrumento == 5) {

		MallaInstrumento->SetStaticMesh(Tom1);
		
		nombre = "Tom1";

	}
	if (id_instrumento == 6) {

		MallaInstrumento->SetStaticMesh(Hi_hat);
		
		nombre = "Hi_hat";
		
	}
	if (id_instrumento == 7) {
		MallaInstrumento->SetStaticMesh(Ride);
	
		MallaInstrumento->SetWorldScale3D( 0.65f*MallaInstrumento->GetRelativeScale3D());
		nombre = "Ride";
	}

}

int AInstrumento::getIdInstrumento() {
	return id_instrumento; //retorna el id del instrumento
}


void AInstrumento::OverlapJugador(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (OtherActor) {

		AJuegoMusicaCharacter* personaje = Cast<AJuegoMusicaCharacter>(OtherActor);


		if (personaje)
		{
			//Aqui extraemos el instrumento correspondiente segun el orden, lo guardamos en un arreglo de enteros, debido a que si toca recolectar instrumentos al unisono, se van a guardar dos posiciones y si no es solo solo una. 
			TArray<int32> posicionRitmo = ritmo->getInstrumentoActual();

			//UE_LOG(LogTemp, Warning, TEXT("Variable CORRECTA: %i"), bEsCorrecto)
			//UE_LOG(LogTemp, Warning, TEXT("Variable es unisono: %i"), ritmo->bEsUnisono)

			//Primero verificamos que no sea un instrumento doble, verificando la variable besunisono que se hace true si el instrumento en la secuancia es mayor a 7, verificamos que no active el boton de unisono, y de una vez verificamos si el intrumento que recolecto el jugar es el que corresponde con el orden del ritmo.
			if (!ritmo->bEsUnisono && !ritmo->bHacerUnisono && this->id_instrumento == posicionRitmo[0])
			{
				bEsCorrecto = true;
			}

			if (ritmo->bEsUnisono && ritmo->bHacerUnisono)
			{
				ritmo->ModificarArregloUnisono(id_instrumento);
				if (ritmo->j == 2 && !ritmo->bSeEquivocaUnisono && ritmo->instrumentos.Num() == 0)
				{
					bEsCorrecto = true;
				} 
			}

/////////////////////////////////////////////////////////////////////////////////
			/*if (!ritmo->bEsUnisono && this->id_instrumento == posicionRitmo[0])
			{
				if (ritmo->bHacerUnisono)
				{
					bEsCorrecto = false;
					ritmo->bActivadoUnisono = true;
					
				} else {
					bEsCorrecto = true;
				}				
			} else {
				if (ritmo->bEsUnisono && ritmo->bHacerUnisono)
				{
					UE_LOG(LogTemp, Warning, TEXT("Variable es unisono: %i"), ritmo->bEsUnisono)
					if (ritmo->j < 2)
					{
						ritmo->ModificarArregloUnisono(id_instrumento);
					}
					
					if (ritmo->j == 2 && !ritmo->bSeEquivocaUnisono && ritmo->instrumentos.Num() == 0)
					{
						UE_LOG(LogTemp, Warning, TEXT("Al unisono completo"))
						bEsCorrecto = true;
					} else {
						UE_LOG(LogTemp, Warning, TEXT("No se completo el unisono"))
					}
				}else{
					UE_LOG(LogTemp, Warning, TEXT("Falta alguna condicion"))
				}
			}*/


			//Cada uno de los if siguientes lo que hacen es reproducir el sonido del instrumento y emitir el efecto de destrucción
			if (id_instrumento == 1) {
					UE_LOG(LogTemp, Warning, TEXT("Tom2"))
					UGameplayStatics::PlaySound2D(this, tom2SoundBase);
					personaje -> PlayCameraInstrumentShake();
					UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			}
			if (id_instrumento == 2) {
				UE_LOG(LogTemp, Warning, TEXT("Caja"))
					UGameplayStatics::PlaySound2D(this, cajaSoundBase);
					personaje -> PlayCameraInstrumentShake();
					UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			}
			if (id_instrumento == 3) {
				UE_LOG(LogTemp, Warning, TEXT("Bombo"))
					UGameplayStatics::PlaySound2D(this, bomboSoundBase);
					personaje -> PlayCameraInstrumentShake();
					UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			}
			if (id_instrumento == 4) {
				UE_LOG(LogTemp, Warning, TEXT("Platillo"))
					UGameplayStatics::PlaySound2D(this, platilloSoundBase);
					personaje -> PlayCameraInstrumentShake();
					UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			}
			if (id_instrumento == 5) {

				UE_LOG(LogTemp, Warning, TEXT("Tom1"))
					UGameplayStatics::PlaySound2D(this, tom1SoundBase);
					personaje -> PlayCameraInstrumentShake();
					UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());	
			}
			if (id_instrumento == 6) {
				UE_LOG(LogTemp, Warning, TEXT("Hi_hat"))
					UGameplayStatics::PlaySound2D(this, hihatSoundBase);
					personaje -> PlayCameraInstrumentShake();
					UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			}
			if (id_instrumento == 7) {
				UE_LOG(LogTemp, Warning, TEXT("Ride"))
					UGameplayStatics::PlaySound2D(this, rideSoundBase);
					personaje -> PlayCameraInstrumentShake();
					UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			}
			
			/*if(ritmo->bEsUnisono && !ritmo->bHacerUnisono)
			{
				//pierde vida 
			}*/

			//UE_LOG(LogTemp, Warning, TEXT("Variable DESPUES CORRECTA: %i"), bEsCorrecto)
			//UE_LOG(LogTemp, Warning, TEXT("Variable DESPUES CORRECTA: %i"), ritmo->j)
			//Verifica si es correcto el intrumento elegido, para asi pasar al siguiente de la secuencia, apesar de que se equivoque sigue al siguiente, y guarda con true or false si lo hizo bien o se equivoco (SOLO CUANDO NO ES AL UNISONO)
			if (bEsCorrecto && !ritmo->bEsUnisono) {
				UE_LOG(LogTemp, Warning, TEXT("Correcto"))			
				ritmo->siguienteInstrumento();
				ritmo->VerificarSecuenciaRitmo.Add(true);
				ritmo->k++;
				PresentarTextosInstance = CreateWidget<UUserWidget>(GetWorld(), TextoCorrecto);
				if (PresentarTextosInstance)
				{
					PresentarTextosInstance->AddToViewport();
				}
			} else if (!bEsCorrecto && !ritmo->bEsUnisono){
				ritmo->VerificarSecuenciaRitmo.Add(false);
				ritmo->siguienteInstrumento();
				personaje->perderVida();
				PresentarTextosInstance = CreateWidget<UUserWidget>(GetWorld(), TextoIncorrecto);
				if (PresentarTextosInstance)
				{
					PresentarTextosInstance->AddToViewport();
				}
			}

			//Verificar si es correcto el unisono elegido, para asi pasar al siguiente instrumento de la secuencia (SOLO CUANDO ES AL UNISONO)
			if (bEsCorrecto && ritmo->bEsUnisono && ritmo->j == 2)
			{
				UE_LOG(LogTemp, Warning, TEXT("Correcto al unisono"))
				ritmo->siguienteInstrumento();
				ritmo->VerificarSecuenciaRitmo.Add(true);
				ritmo->j = 0;
				ritmo->k++;
				PresentarTextosInstance = CreateWidget<UUserWidget>(GetWorld(), TextoCorrecto);
				if (PresentarTextosInstance)
				{
					PresentarTextosInstance->AddToViewport();
				}
			} else if(!bEsCorrecto && ritmo->bEsUnisono && ritmo->j == 2){
				ritmo->siguienteInstrumento();
				ritmo->VerificarSecuenciaRitmo.Add(false);
				personaje->perderVida();
				PresentarTextosInstance = CreateWidget<UUserWidget>(GetWorld(), TextoIncorrecto);
				if (PresentarTextosInstance)
				{
					PresentarTextosInstance->AddToViewport();
				}
			} else if(!bEsCorrecto && !ritmo->bHacerUnisono && ritmo->bEsUnisono){
				ritmo->siguienteInstrumento();
				ritmo->VerificarSecuenciaRitmo.Add(false);
				personaje->perderVida();
				PresentarTextosInstance = CreateWidget<UUserWidget>(GetWorld(), TextoError1);
				if (PresentarTextosInstance)
				{
					PresentarTextosInstance->AddToViewport();
				}
			}
			
			//Sentencia para llamar al método que verifica si ha cumplido con el ritmo correctamente o verificar en que partes se ha equivoado sin perder las vidas.
			if (ritmo->i == ritmo->getTamSecuencia())
			{
				
				ritmo->VerificarRitmoCorrecto();
				personaje->MoverPersonajeGanador();
				AdministradorInstrumentos->ApagarGenerador();			
			}

			// Sentencia para reproducir el sonido al momento de perder las tres vidas
			if (personaje->vidas < 1)
			{
				UGameplayStatics::SpawnSound2D(this, sonidoPerder);
			}
			
			Destroy(); // se destruye el instrumento cada vez que choca con el actor
		}
		else if (OtherActor->GetClass()->GetName().Equals(TEXT("BP_BloquesLimitadores_C")))
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
			Destroy();
			
		}

		//UE_LOG(LogTemp, Warning, TEXT("NOmbre: %s"), *OtherActor->GetClass()->GetName());
	}

}