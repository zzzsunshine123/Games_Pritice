// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	NetUpdateFrequency = 100.f;
}

void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AAuraPlayerState,Level);
		
	DOREPLIFETIME(AAuraPlayerState,XP);
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{

	return AbilitySystemComponent;
}

void AAuraPlayerState::SetXP(int inXP)
{
	XP=inXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::AddToXP(int inXP)
{
	XP+=inXP;
	OnXPChangedDelegate.Broadcast(XP);
}
int32 AAuraPlayerState::GetXP()
{
	return  XP;
}

 void AAuraPlayerState::SetLevel(int inLevel)
{
	Level=inLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::AddToLevel(int inLevel)
{
	Level+=inLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

 int32 AAuraPlayerState::GetPlayerLevel() const
{
	return Level;
}
void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void AAuraPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}

