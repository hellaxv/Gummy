// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "DamageTarget.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*Collision = CreateDefaultSubobject<USphereComponent>("Collision");
	RootComponent = Collision;

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);*/

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
	
	AudioEffect = CreateDefaultSubobject<UAudioComponent>("AudioEffect");
	AudioEffect->SetupAttachment(Mesh);

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>("ShootEffect");
	ShootEffect->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::MoveTick, MoveRate, true);
	GetWorld()->GetTimerManager().SetTimer(TimerDestroySeconds, this, &AProjectile::SelfDestroy, SelfDestroySeconds, false);
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
		return;
	GetWorld()->GetTimerManager().ClearTimer(Timer);


	auto Target = Cast<IDamageTarget>(OtherActor);
	if (Target)
	{
		FDamageData DamageData;
		DamageData.DamageValue = Damage;
		DamageData.Instigator = this;
		Target->TakeDamage(DamageData);
	}

	auto Root = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
	if (Root && Root->IsSimulatingPhysics())
	{
		Root->AddImpulseAtLocation(GetActorForwardVector() * MoveSpeed * 100, SweepResult.Location);
	}
	
	auto Temp = GetActorLocation();

	ShootEffect->ActivateSystem();
	AudioEffect->Play();

	SetActorLocation({-3000,-3000,-3000});
	ShootEffect->SetWorldLocation(Temp);
	AudioEffect->SetWorldLocation(Temp);
	//Destroy();
	//OtherActor->Destroy();
}

void AProjectile::MoveTick()
{
	auto Location = GetActorLocation();
	SetActorLocation(Location + GetActorForwardVector() * MoveRate * MoveSpeed, true); 
}

void AProjectile::SelfDestroy()
{
	Destroy();
}

/*
// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
*/
