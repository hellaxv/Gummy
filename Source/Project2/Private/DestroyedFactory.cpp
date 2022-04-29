// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyedFactory.h"

#include "Particles/ParticleSystemComponent.h"

// Sets default values
ADestroyedFactory::ADestroyedFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("DefaultRoot");
	
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh");
	BuildingMesh->SetupAttachment(RootComponent);

	CreateEffect = CreateDefaultSubobject<UParticleSystemComponent>("CreateEffect");
	CreateEffect->SetupAttachment(BuildingMesh);

}

// Called when the game starts or when spawned
void ADestroyedFactory::BeginPlay()
{
	Super::BeginPlay();
	CreateEffect->ActivateSystem();
}

// Called every frame
void ADestroyedFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

