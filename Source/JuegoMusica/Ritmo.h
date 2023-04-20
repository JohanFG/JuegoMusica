// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AdministradorDeInstrumentos.h"
#include "GameFramework/Actor.h"
#include "Ritmo.generated.h"

UCLASS()
class JUEGOMUSICA_API ARitmo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARitmo();
	UPROPERTY(EditAnywhere)
	int idInstrumentoActual; // id del instrumento que es el correcto 
	UPROPERTY(EditAnywhere)
	int idInstrumentoSiguiente; // id del siguiente instrumento correcto 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int dificultad; // numero que define la dificultad 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ritmo;
	UFUNCTION()
	TArray<int32> getInstrumentoActual(); // obtiene el id del instrumento actual 

	//Devuelve el arreglo que verifica cada instrumento elegido
	UFUNCTION()
	TArray<bool> getVerificarSecuenciaRitmo();

	UFUNCTION()
	int getInstrumentoSiguiente();

	UFUNCTION()
	int getDificultadActual();// obtiene el id del isntrumento siguiente si existe
	
	UFUNCTION()
	void siguienteInstrumento(); // obtiene el siguiente instrumento una vez tocado el correcto o la secuencia correcta

	UFUNCTION()
	int32 getTamSecuencia();

	//Verifica si es correcto todo el ritmo
	UFUNCTION()
	void VerificarRitmoCorrecto();

	/*UFUNCTION()
	void IntercambiarInstrumento(int& siguiente, int& actual);
	UFUNCTION()
	void Intercambiar();
	UFUNCTION()
	bool bEsUnisonoElSiguiente(); // depende si el siguiente instrumento es unisono*/
	UFUNCTION()
	void AsignarRitmo(int& dif, int& rit);
	UFUNCTION()
	void ModificarArregloUnisono(int& id);
	UPROPERTY(BlueprintReadOnly)
	int i = 0; // contador para la totalidad de instrumentos

	UPROPERTY(BlueprintReadOnly)
	int j = 0; // contador para verificar que recoja dos instrumentos al unisono

	UPROPERTY(BlueprintReadOnly)
	int k = 0; // contador para los correctos

	// Esta variable cambia a true cuando se aplasta el boton de unisono.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHacerUnisono = false; 

	// Verdadero o falso, depende del número correspondiente en la secuencia, si es un número de 2 digitos, se hace verdadero.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEsUnisono = false; 

	//Esta variable se cambia cuando elige un instrumento equivocado al momento de ser unisono
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bSeEquivocaUnisono = false;

	//Verifica si ha elegido todos los instrumentos correctos en la secuencia
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTodoEsCorrecto = false;

	//Verifica si ha dejado activado el boton de unisono
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bActivadoUnisono = false;

	//Sonido para cuando complete correctamente todo el ritmo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* sonidoGanar; 

	//Sonido para cuando complete no al 100% el ritmo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* sonidoCulminar; 

	//Arreglos para guardar las secuencias de los ritmos presentados en el juego
	TArray<int32> facil1;
	TArray<int32> facil2;
	TArray<int32> facil3;
	TArray<int32> facil4;

	TArray<int32> medio1;
	TArray<int32> medio2;
	TArray<int32> medio3;
	TArray<int32> medio4;
	
	TArray<int32> dificil1;
	TArray<int32> dificil2;
	TArray<int32> dificil3;
	TArray<int32> dificil4;
	
	//Aqui se guarda valores booleano según lo que el jugador va recolectando, si recolecta un instrumento que no se eencuentra en la secuancia de ritmo elegida se guarda como falso.
	UPROPERTY(BlueprintReadOnly)
	TArray<bool> VerificarSecuenciaRitmo;

	//En este arreglo se guarda la secuencia que eligio el jugador para replicar
	UPROPERTY(BlueprintReadOnly)
	TArray<int32> secuencia;

	//Variable para guardar la dimension del arreglo de la secuencia
	UPROPERTY(BlueprintReadOnly)
	int32 tamSecuencia;

	//arreglo para guardar los instrumentos que se recogeran al unisono
	TArray<int32> instrumentos;

	//variables para presentar en la pantalla el widget de resultados
	UPROPERTY(EditAnywhere) 
	TSubclassOf<UUserWidget> PresentarInstrumentos;

	UUserWidget* PresentarInstrumentosInstance;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
