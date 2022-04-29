// Fill out your copyright notice in the Description page of Project Settings.


#include "SprayProjectile.h"

#include "DamageTarget.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASprayProjectile::ASprayProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*Collisions = CreateDefaultSubobject<USphereComponent>("Collisions");
	RootComponent = Collisions;

	Collisions->OnComponentBeginOverlap.AddDynamic(this, &ASprayProjectile::OnBeginOverLaps);

	Cash = CreateDefaultSubobject<UStaticMeshComponent>("Cash");
	Cash->SetupAttachment(RootComponent);*/

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASprayProjectile::OnBeginOverLaps);
	
	AudioEffect = CreateDefaultSubobject<UAudioComponent>("AudioEffect");
	AudioEffect->SetupAttachment(Mesh);

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>("ShootEffect");
	ShootEffect->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void ASprayProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(Time, this, &ASprayProjectile::MoveTicks, MoveRate, true);
	GetWorld()->GetTimerManager().SetTimer(TimerDestroySeconds, this, &ASprayProjectile::SelfDestroy, SelfDestroySeconds, false);
}

void ASprayProjectile::OnBeginOverLaps(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;
	GetWorld()->GetTimerManager().ClearTimer(Time);

	auto Target = Cast<IDamageTarget>(OtherActor);
	if (Target)
	{
		FDamageData DamageData;
		DamageData.DamageValue = Damages;
		DamageData.Instigator = this;
		Target->TakeDamage(DamageData);
	}
	auto Temp = GetActorLocation();

	ShootEffect->ActivateSystem();
	AudioEffect->Play();

	SetActorLocation({-3000,-3000,-3000});
	ShootEffect->SetWorldLocation(Temp);
	AudioEffect->SetWorldLocation(Temp);
}

void ASprayProjectile::MoveTicks()
{
	auto Locations = GetActorLocation();
	SetActorLocation(Locations + GetActorForwardVector() * MoveRate * MoveSpeeds, true);
}

void ASprayProjectile::SelfDestroy()
{
	Destroy();
}

/*
// Called every frame
void ASprayProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
