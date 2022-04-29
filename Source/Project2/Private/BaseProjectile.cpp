// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

#include "Projectile.h"
#include "SprayProjectile.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	RootComponent = Collision;

	//Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	//SPRAYPROJECTILE
	/*Collisions = CreateDefaultSubobject<USphereComponent>("Collisions");
	RootComponent = Collisions;

	//Collisions->OnComponentBeginOverlap.AddDynamic(this, &ASprayProjectile::OnBeginOverLaps);

	Cash = CreateDefaultSubobject<UStaticMeshComponent>("Cash");
	Cash->SetupAttachment(RootComponent);*/
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

