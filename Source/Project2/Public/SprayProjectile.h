// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SprayProjectile.generated.h"

UCLASS()
class PROJECT2_API ASprayProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprayProjectile();

	//S-приставка, запомнить!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* Collisions;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* Cash;*/

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UParticleSystemComponent* ShootEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Components")
	UAudioComponent* AudioEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Fire Projectile")
	int SelfDestroySeconds = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Spray Projectile")
	float MoveSpeeds = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Spray Projectile")
	float MoveRate = 0.05;
	
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Spray Projectile")
	float Damages = 0.2;*/
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FTimerHandle Time;
	FTimerHandle TimerDestroySeconds;

	UFUNCTION()
	void OnBeginOverLaps(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	void MoveTicks();
	void SelfDestroy();
	
/*
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
*/
};
