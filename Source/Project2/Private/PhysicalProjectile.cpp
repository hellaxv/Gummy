// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicalProjectile.h"

#include "DamageTarget.h"

APhysicalProjectile::APhysicalProjectile()
{
	Collision->SetSimulatePhysics(true);
	Collision->BodyInstance.bNotifyRigidBodyCollision = true;
	
	MovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	
	AffectedArea=CreateDefaultSubobject<USphereComponent>("AffectedArea");
	AffectedArea->SetupAttachment(RootComponent);

}

void APhysicalProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	TArray<FHitResult> Targets;
	GetWorld()->SweepMultiByChannel(Targets, GetActorLocation(), GetActorLocation(), GetActorRotation().Quaternion(), ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(AffectedArea->GetScaledSphereRadius()));

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

		if (Cast<ABaseProjectile>(HitTarget.Actor))
		{
			continue;
		}

		auto Root = Cast<UPrimitiveComponent>(HitTarget.Actor->GetRootComponent());
		if (Root && Root->IsSimulatingPhysics())
		{
			auto Impulse = GetActorForwardVector() * 10000;
			Root->AddImpulseAtLocation(Impulse, HitTarget.Location);
		}
	}
	Destroy();
}

void APhysicalProjectile::Move()
{
	
}

void APhysicalProjectile::Explode()
{
	
}
