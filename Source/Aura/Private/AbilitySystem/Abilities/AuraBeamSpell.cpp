// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraBeamSpell::StoreMouseDataInfo(const FHitResult& HitResult)
{
	if(HitResult.bBlockingHit)
	{
		MouseHitLocation=HitResult.ImpactPoint;
		MouseHitActor=HitResult.GetActor();
	}
	else
	{
		CancelAbility(CurrentSpecHandle,CurrentActorInfo,CurrentActivationInfo,true);
	}
}

void UAuraBeamSpell::StoreOwnerVariables()
{
	if(CurrentActorInfo)
	{
		OwnerPlayerController=CurrentActorInfo->PlayerController.Get();
		OwnerCharacter=Cast<ACharacter>(CurrentActorInfo->AvatarActor);
	}
}

void UAuraBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	check(OwnerCharacter);
	if(OwnerCharacter->Implements<UCombatInterface>())
	{
		if(USkeletalMeshComponent* Weapon=ICombatInterface::Execute_GetWeapon(OwnerCharacter))
		{
			TArray<AActor*>ActorsToIgnore;
			ActorsToIgnore.Add(OwnerCharacter);
			FHitResult HitResult;
			
			const FVector SocketLocation=Weapon->GetSocketLocation(FName("TipSocket"));
			UKismetSystemLibrary::SphereTraceSingle(
				OwnerCharacter,
				SocketLocation,
				BeamTargetLocation,
				10.f,
				TraceTypeQuery1,
				false,
				ActorsToIgnore,
				EDrawDebugTrace::None,
				HitResult,
				true
				);

			if(HitResult.bBlockingHit)
			{
				MouseHitLocation=HitResult.Location;
				MouseHitActor=HitResult.GetActor();
			}
		}
	}

	if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(MouseHitActor))
	{
		if(!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this,&UAuraBeamSpell::PrimaryTargetDied))
		{
			CombatInterface->GetOnDeathDelegate().AddDynamic(this,&UAuraBeamSpell::PrimaryTargetDied);
		}
	}
}

void UAuraBeamSpell::StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets)
{
	TArray<AActor*>ActorsToIgnore;
	ActorsToIgnore.Add(OwnerCharacter);
	ActorsToIgnore.Add(MouseHitActor);

	TArray<AActor*>OverlappingActors;
	UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(
       OwnerCharacter,
       OverlappingActors,
       ActorsToIgnore,
       850.f,
       MouseHitActor->GetActorLocation());

	int32 NumAdditionalTargets=FMath::Min(GetAbilityLevel(),MaxNumShockTargets);

	UAuraAbilitySystemLibrary::GetClosestTargets(NumAdditionalTargets,OverlappingActors,
		OutAdditionalTargets,MouseHitActor->GetActorLocation());


	for(auto target:OutAdditionalTargets)
	{
		if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(target))
		{
			if(!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this,&UAuraBeamSpell::AdditionalTargetDied))
			{
				CombatInterface->GetOnDeathDelegate().AddDynamic(this,&UAuraBeamSpell::AdditionalTargetDied);
			}
		}
	}
}

FString UAuraBeamSpell::GetDescription(int32 Level)
{
	const int32 ScaledDamage =Damage.GetValueAtLevel(GetAbilityLevel());
	
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCoolDown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>ELECTROCUTE</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
			"<Default>Emits a beam of lightning, "
			"connecting with the target, repeatedly causing </>"

			// Damage
			"<Damage>%d</><Default> lightning damage with"
			" a chance to stun</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>ELECTROCUTE</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Addition Number of Shock Targets
			"<Default>Emits a beam of lightning, "
			"propagating to %d additional targets nearby, causing </>"

			// Damage
			"<Damage>%d</><Default> lightning damage with"
			" a chance to stun</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumShockTargets - 1),
			ScaledDamage);		
	}
}

FString UAuraBeamSpell::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCoolDown(Level);
	return FString::Printf(TEXT(
			// Title
			"<Title>NEXT LEVEL:</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Addition Number of Shock Targets
			"<Default>Emits a beam of lightning, "
			"propagating to %d additional targets nearby, causing </>"

			// Damage
			"<Damage>%d</><Default> lightning damage with"
			" a chance to stun</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumShockTargets - 1),
			ScaledDamage);	
}
