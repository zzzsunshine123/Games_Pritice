// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "AuraGameplayTags.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation,const FGameplayTag& SocketTag,bool bOverridePitch,float PitchOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if(!bIsServer) return;


	const FVector SockteLocation =ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(),SocketTag);
	FRotator Rotation = (ProjectileTargetLocation-SockteLocation).Rotation();
		
	FTransform SpawnTransform;
	if(bOverridePitch)
	{
		Rotation.Pitch=PitchOverride;
	}
	SpawnTransform.SetLocation(SockteLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
		
	AAuraProjectile* Projectile=GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	Projectile->DamageEffectParams=MakeDamageEffectParamsFromClassDefaults();
		
	Projectile->FinishSpawning(SpawnTransform);
}

