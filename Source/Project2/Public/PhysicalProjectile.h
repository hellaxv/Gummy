// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicalProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2_API APhysicalProjectile : public ABaseProjectile
{
	GENERATED_BODY()

public:
	APhysicalProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* AffectedArea;
	
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	void Move();
	void Explode();
};
