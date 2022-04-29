// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFactory.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABaseFactory::ABaseFactory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("DefaultRoot");
	
	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>("BuildingMesh");
	BuildingMesh->SetupAttachment(RootComponent);

	HitCollider = CreateDefaultSubobject<UBoxComponent>("HitCollider");
	HitCollider->SetupAttachment(RootComponent);

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HealthComponent->OnHealthChanged.AddUObject(this, &ABaseFactory::OnHealthChanged);
	HealthComponent->OnDestroy.AddUObject(this, &ABaseFactory::OnDestroy);

	DestroyedEffect = CreateDefaultSubobject<UParticleSystemComponent>("DestroyedEffect");
	DestroyedEffect->SetupAttachment(BuildingMesh);
	
	AudioDestroyedEffect = CreateDefaultSubobject<UAudioComponent>("AudioDestroyedEffect");
	AudioDestroyedEffect->SetupAttachment(BuildingMesh);

	CreateEffect = CreateDefaultSubobject<UParticleSystemComponent>("CreateEffect");
	CreateEffect->SetupAttachment(BuildingMesh);
	
	AudioCreateEffect = CreateDefaultSubobject<UAudioComponent>("AudioCreateEffect");
	AudioCreateEffect->SetupAttachment(BuildingMesh);

	DestroyedFactorySpawnPoint = CreateDefaultSubobject<UArrowComponent>("DestroyedFactorySpawnPoint");
	DestroyedFactorySpawnPoint->SetupAttachment(RootComponent);
	
}

void ABaseFactory::TakeDamage(FDamageData Damage)
{
	if (HealthComponent)
		HealthComponent->TakeDamage(Damage);
}

// Called when the game starts or when spawned
void ABaseFactory::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseFactory::OnTankSpawnTick, SpawnInterval, true);
}

// Called every frame
void ABaseFactory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseFactory::OnTankSpawnTick()
{
	if (CreateEffect && AudioCreateEffect)
	{
		CreateEffect->ActivateSystem();
		AudioCreateEffect->Play();
		if(TanksSpawned > MaxTanks )
			return;
	}
	////////////////////////////////////////////////////////
	auto Tank = GetWorld()->SpawnActorDeferred<AEnemyTank_Pawn>(TankClass, SpawnPoint->GetComponentTransform());
	Tank->Waypoints = Waypoints;
	TanksSpawned++;
	Tank->Number = TanksSpawned;
	UGameplayStatics::FinishSpawningActor(Tank, SpawnPoint->GetComponentTransform());
}

void ABaseFactory::OnDestroy()
{
	auto Temp = GetActorLocation();
	DestroyedEffect->ActivateSystem();
	AudioDestroyedEffect->Play();
	GetWorld()->SpawnActor<ADestroyedFactory>(DestroyedFactoryClass,DestroyedFactorySpawnPoint->GetComponentLocation(),DestroyedFactorySpawnPoint->GetComponentRotation());
	SetActorLocation({-1000, -1000, -1000});
	//DestroyFabric->SetActorLocation(Temp);
	DestroyedEffect->SetWorldLocation(Temp);
	AudioDestroyedEffect->SetWorldLocation(Temp);
	GetWorld()->GetTimerManager().SetTimer(TimerDestroyed,this,&ABaseFactory::MyselfDestroy,3,false);
	GEngine->AddOnScreenDebugMessage(9872, 3, FColor::White,FString::Printf(TEXT("ENEMY FACTORY DESTROYED!")));
	GetWorldTimerManager().ClearTimer(TimerHandle);
	if (LevelTrigger)
	{
		LevelTrigger->SetActive(true);
	}
}

void ABaseFactory::OnHealthChanged(float CurrentHealth)
{
	GEngine->AddOnScreenDebugMessage(98716, 3, FColor::Yellow,FString::Printf(TEXT("HP ENEMY FACTORY: %f"), CurrentHealth));
}

void ABaseFactory::MyselfDestroy()
{
	Destroy();
}

