// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalSprayProjectile.h"

#include "DamageTarget.h"

APhysicalSprayProjectile::APhysicalSprayProjectile()
{
	Collision->SetSimulatePhysics(true);
	Collision->BodyInstance.bNotifyRigidBodyCollision = true;
	
	MovementComponents=CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");

	AffectedArea=CreateDefaultSubobject<USphereComponent>("AffectedArea");
	AffectedArea->SetupAttachment(RootComponent);
	
}

void APhysicalSprayProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	TArray<FHitResult> Targets;
	GetWorld()->SweepMultiByChannel(Targets, GetActorLocation(), GetActorLocation(), GetActorRotation().Quaternion(), ECollisionChannel::ECC_GameTraceChannel1, FCollisionShape::MakeSphere(AffectedArea->GetScaledSphereRadius()));

	for (auto& HitTarget : Targets)
	{
		auto Target = Cast<IDamageTarget>(HitTarget.Actor);
		if (Target)
		{
			FDamageData DamageData;
			DamageData.DamageValue = Damage;
			DamageData.Instigator = this;
			Target->TakeDamage(DamageData);
		}

		auto Root = Cast<UPrimitiveComponent>(HitTarget.Actor->GetRootComponent());
		if (Root && Root->IsSimulatingPhysics())
		{
			Root->AddImpulseAtLocation(MovementComponents->GetPendingForce() * 1000 / FVector::Distance(HitTarget.Location, GetActorLocation()), HitTarget.Location);
		}
	}
	Destroy();
}
