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
	DOREPLIFETIME(AAuraPlayerState,AttributePoints);
	DOREPLIFETIME(AAuraPlayerState,SpellPoints);

	
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

void AAuraPlayerState::SetAttributePoints(int inAttributesPoints)
{
	AttributePoints=inAttributesPoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

void AAuraPlayerState::AddToAttributePoints(int inAttributePoints)
{
	AttributePoints+=inAttributePoints;
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

int32 AAuraPlayerState::GetAttributePoints()
{
	return  AttributePoints;
}


 void AAuraPlayerState::SetSpellPoints(int inSpellPoints)
{
	SpellPoints=inSpellPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

 void AAuraPlayerState::AddToSpellPoints(int inSpellPoints)
{
	SpellPoints+=inSpellPoints;
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}

 int32 AAuraPlayerState::GetSpellPoints()
{
	return SpellPoints;
}

void AAuraPlayerState::SetLevel(int inLevel)
{
	Level=inLevel;
	OnLevelChangedDelegate.Broadcast(Level,false);
}



void AAuraPlayerState::AddToLevel(int inLevel)
{
	Level+=inLevel;
	OnLevelChangedDelegate.Broadcast(Level,true);
}

 int32 AAuraPlayerState::GetPlayerLevel() const
{
	return Level;
}
void AAuraPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level,true);
}

void AAuraPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}

void AAuraPlayerState::OnRep_AttributePoints(int32 OldAttributePoints)
{
	OnAttributePointsChangedDelegate.Broadcast(AttributePoints);
}

 void AAuraPlayerState::OnRep_SpellPoints(int32 OldSpell)
{
	OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
}



