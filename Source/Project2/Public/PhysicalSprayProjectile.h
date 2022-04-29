// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicalSprayProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT2_API APhysicalSprayProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:
	APhysicalSprayProjectile();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UProjectileMovementComponent* MovementComponents;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* AffectedArea;

	
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
