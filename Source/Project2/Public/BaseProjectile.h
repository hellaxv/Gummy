// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class PROJECT2_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Projectile")
	float Damage = 1;

	//////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Spray Projectile")
	float Damages = 0.2;

	//SPRAYPROJECTILE
	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* Collisions;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* Cash;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Spray Projectile")
	float Damages = 0.2;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
