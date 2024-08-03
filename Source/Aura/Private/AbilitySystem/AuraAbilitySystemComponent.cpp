// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Chaos/ChaosPerfTest.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Aura/AuraLogChannels.h"
#include "Interaction/PlayerInterface.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this,&UAuraAbilitySystemComponent::ClientEffectApplied);
	

	 
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
for(const auto AbilityClass:StartupAbilities)
{
	 FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
	
	 if(const UAuraGameplayAbility* AuraAbility=Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
	 {
		AbilitySpec.DynamicAbilityTags.AddTag(AuraAbility->StartupInputTag);
	 	AbilitySpec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Abilities_Status_Equipped);
	 	GiveAbility(AbilitySpec);
	 }
}
	bStartupAbilitiesGiven=true;
    AbilitiesGivenDelegate.Broadcast();
}

void UAuraAbilitySystemComponent::AddCharacterPassiveAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities)
{
	for(const auto AbilityClass:StartupPassiveAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass,1);
	
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
	
}

void UAuraAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLock(*this);
	for(FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if(AbilitySpec.IsActive())
			{
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed,AbilitySpec.Handle,AbilitySpec.ActivationInfo.GetActivationPredictionKey());
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLock(*this);
	for(FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if(!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid()) return;
	FScopedAbilityListLock ActiveScopeLock(*this);
	for(FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)&&AbilitySpec.IsActive())
		{
			AbilitySpecInputReleased(AbilitySpec);

			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased,AbilitySpec.Handle,AbilitySpec.ActivationInfo.GetActivationPredictionKey());
		
		}
	}
}

void UAuraAbilitySystemComponent::ForEachAbility(const FForEachAbility& Delegate)
{
  FScopedAbilityListLock ActiveScopeLock(*this);

	for(const FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		if(!Delegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogAura,Error,TEXT("Failed to execute delegate in %hs"),__FUNCTION__);
		}
	}
	
}

FGameplayTag UAuraAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if(AbilitySpec.Ability)
	{
		for(FGameplayTag Tag: AbilitySpec.Ability.Get()->AbilityTags)
		{
			if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities"))))
			{
				return  Tag;
			}
		}
	}
	return FGameplayTag();
}

FGameplayTag UAuraAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for(FGameplayTag Tag : AbilitySpec.DynamicAbilityTags)
	{
		if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag"))))
		{
			return  Tag;
		}
	}
	return FGameplayTag();
}

FGameplayTag UAuraAbilitySystemComponent::GetStatusTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for(FGameplayTag Tag : AbilitySpec.DynamicAbilityTags)
	{
		if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities.Status"))))
		{
			return  Tag;
		}
	}
	return FGameplayTag();
}

FGameplayTag UAuraAbilitySystemComponent::GetstatusFromAbilityTag(const FGameplayTag& AbilityTag)
{
	if(const FGameplayAbilitySpec* spec=GetSpecFromAbilityTag(AbilityTag))
	{
		return GetStatusTagFromSpec(*spec);
	}
	return FGameplayTag();
}

FGameplayTag UAuraAbilitySystemComponent::GetInputTagFromAbilityTag(const FGameplayTag& AbilityTag)
{
	if(const FGameplayAbilitySpec* spec=GetSpecFromAbilityTag(AbilityTag))
	{
		return GetInputTagFromSpec(*spec);
	}
	return FGameplayTag();
}

bool UAuraAbilitySystemComponent::SoltIsEmpty(const FGameplayTag& Slot)
{
	FScopedAbilityListLock ActiveScopeLock(*this);

	for(FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		if(AbilityHasSlot(AbilitySpec,Slot))
		{
			return false;
		}
	}
	return true;
	
}

bool UAuraAbilitySystemComponent::AbilityHasSlot(const FGameplayAbilitySpec& Spec, const FGameplayTag& Slot)
{
	return Spec.DynamicAbilityTags.HasTagExact(Slot);
}

bool UAuraAbilitySystemComponent::AbilityHasAnySlot(const FGameplayAbilitySpec& Spec)
{
	return Spec.DynamicAbilityTags.HasTag(FGameplayTag::RequestGameplayTag(FName("InputTag")));
}

FGameplayAbilitySpec* UAuraAbilitySystemComponent::GetSpecWithSlot(const FGameplayTag& Slot)
{
	FScopedAbilityListLock ActiveScopeLock(*this);

	for(FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		if(AbilitySpec.DynamicAbilityTags.HasTagExact(Slot))
		{
			return &AbilitySpec;
		}
	}
	return nullptr;
}

bool UAuraAbilitySystemComponent::IsPassiveAbility(const FGameplayAbilitySpec& Spec) 
{
	UAbilityInfo* AbilityInfo=UAuraAbilitySystemLibrary::GetAbilityInfo(GetAvatarActor());
	FGameplayTag AbilityTag=GetAbilityTagFromSpec(Spec);
	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	FGameplayTag AbilityType=Info.AbilityType;
	return AbilityType.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Type_Passive);
}

void UAuraAbilitySystemComponent::AssignSlotToAbility(FGameplayAbilitySpec& Spec, const FGameplayTag& Slot)
{
	ClearSlot(&Spec);
	Spec.DynamicAbilityTags.AddTag(Slot);
}

void UAuraAbilitySystemComponent::MulticastActivatePassiveEffect_Implementation(const FGameplayTag& AbilityTag,
	bool bActivate)
{
	ActivePassiveEffect.Broadcast(AbilityTag,bActivate);
}

FGameplayAbilitySpec* UAuraAbilitySystemComponent::GetSpecFromAbilityTag(const FGameplayTag& AbilityTag)
{
    FScopedAbilityListLock ActiveScopeLock(*this);

	for(FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		for(FGameplayTag Tag:AbilitySpec.Ability.Get()->AbilityTags)
		{
			if(Tag.MatchesTag(AbilityTag))
			{
				return &AbilitySpec;
			}
		}
	}
	return nullptr;
	
}

void UAuraAbilitySystemComponent::UpGradeAttribute(const FGameplayTag& AttributeTag)
{

	if(GetAvatarActor()->Implements<UPlayerInterface>())
	{
		if(IPlayerInterface::Execute_GetAttributePoints(GetAvatarActor())>0)
		{
			ServerUpGradeAttribute(AttributeTag);
		}
	}
}

void UAuraAbilitySystemComponent::ServerUpGradeAttribute_Implementation(const FGameplayTag& AttributeTag)
{
	FGameplayEventData Playload;
	Playload.EventTag = AttributeTag;
	Playload.EventMagnitude=1.f;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(),AttributeTag,Playload);

	if(GetAvatarActor()->Implements<UPlayerInterface>())
	{
		IPlayerInterface::Execute_AddToAttributePoints(GetAvatarActor(),-1);
	}
}

void UAuraAbilitySystemComponent::UpdateAbilityStatus(int32 Level)
{
	UAbilityInfo* AbilityInfo=UAuraAbilitySystemLibrary::GetAbilityInfo(GetAvatarActor());

	for(const FAuraAbilityInfo& Info : AbilityInfo->AbilityInformation)
	{
		if(!Info.AbilityTag.IsValid()) continue;
		if(Level<Info.LevelRequirement)continue;
		if(GetSpecFromAbilityTag(Info.AbilityTag)==nullptr) //等级达到要求，还未激活技能
		{
			FGameplayAbilitySpec AbilitySpec= FGameplayAbilitySpec(Info.Ability,1);
			AbilitySpec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Abilities_Status_Eligible);
			GiveAbility(AbilitySpec);
			MarkAbilitySpecDirty(AbilitySpec);

			ClientUpdateAbilityStatus(Info.AbilityTag,FAuraGameplayTags::Get().Abilities_Status_Eligible,1);
			
		}
	}
	
}

void UAuraAbilitySystemComponent::ServerSpendSpellPoint_Implementation(const FGameplayTag& AbilityTag)
{
	if (FGameplayAbilitySpec* AbilitySpec = GetSpecFromAbilityTag(AbilityTag))
	{
		if (GetAvatarActor()->Implements<UPlayerInterface>())
		{
			IPlayerInterface::Execute_AddToSpellPoints(GetAvatarActor(), -1);
		}
		
		const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
		FGameplayTag Status = GetStatusTagFromSpec(*AbilitySpec);
		if (Status.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
		{
			AbilitySpec->DynamicAbilityTags.RemoveTag(GameplayTags.Abilities_Status_Eligible);
			AbilitySpec->DynamicAbilityTags.AddTag(GameplayTags.Abilities_Status_Unlocked);
			Status = GameplayTags.Abilities_Status_Unlocked;
		}
		else if (Status.MatchesTagExact(GameplayTags.Abilities_Status_Equipped) || Status.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
		{
			AbilitySpec->Level += 1;
		}
		ClientUpdateAbilityStatus(AbilityTag, Status, AbilitySpec->Level);
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::ServerEquipAbility_Implementation(const FGameplayTag& AbilityTag,
	const FGameplayTag& slot)
{
	if (FGameplayAbilitySpec* AbilitySpec = GetSpecFromAbilityTag(AbilityTag))
	{
		const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
		const FGameplayTag& PrevSlot = GetInputTagFromSpec(*AbilitySpec);
		const FGameplayTag& Status = GetStatusTagFromSpec(*AbilitySpec);

		const bool bStatusValid = Status == GameplayTags.Abilities_Status_Equipped || Status == GameplayTags.Abilities_Status_Unlocked;
		if (bStatusValid)
		{

			// Handle activation/deactivation for passive abilities

             if(!SoltIsEmpty(slot))
             {
	             FGameplayAbilitySpec* SpecWithSlot = GetSpecWithSlot(slot);
             	if(SpecWithSlot)
             	{
             		if(AbilityTag.MatchesTagExact(GetAbilityTagFromSpec(*SpecWithSlot)))
             		{
             			ClientEquipAbility(AbilityTag, GameplayTags.Abilities_Status_Equipped, slot, PrevSlot);
             			return;
             		}
             		if(IsPassiveAbility(*SpecWithSlot))
             		{
             			MulticastActivatePassiveEffect(GetAbilityTagFromSpec(*SpecWithSlot),false);
             			DeactivatePassiveAbility.Broadcast(GetAbilityTagFromSpec(*SpecWithSlot));
             		}
             		ClearSlot(SpecWithSlot);
             	}
             
             }

			if(!AbilityHasAnySlot(*AbilitySpec))
			{
				if(IsPassiveAbility(*AbilitySpec))
				{
					TryActivateAbility(AbilitySpec->Handle);
					MulticastActivatePassiveEffect(AbilityTag,true);
				}
			}
			AssignSlotToAbility(*AbilitySpec,slot);
			

			/*
			ClearAbilitiesOfSlot(slot); //先移除所有 有这个slot inputTag的技能的inputTag
			ClearSlot(AbilitySpec);  //移除这个技能的inputTag

			AbilitySpec->DynamicAbilityTags.AddTag(slot); //为这个技能配备这个inputTag
			if(Status.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
			{
				AbilitySpec->DynamicAbilityTags.RemoveTag(GameplayTags.Abilities_Status_Unlocked);
				AbilitySpec->DynamicAbilityTags.AddTag(GameplayTags.Abilities_Status_Equipped);
			}	*/

			MarkAbilitySpecDirty(*AbilitySpec);
		
		}
			
		ClientEquipAbility(AbilityTag, GameplayTags.Abilities_Status_Equipped, slot, PrevSlot);
		
	}
}

void UAuraAbilitySystemComponent::ClientEquipAbility_Implementation(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
	const FGameplayTag& Slot, const FGameplayTag& PreviousSlot)
{
	AbilityEquipped.Broadcast(AbilityTag,Status,Slot,PreviousSlot);
}

bool UAuraAbilitySystemComponent::GetDescriptionsByAbilityTag(const FGameplayTag& AbilityTag, FString& OutDescription,
                                                              FString& OutNextLevelDescription)
{
	if (const FGameplayAbilitySpec* AbilitySpec = GetSpecFromAbilityTag(AbilityTag))
	{
		if(UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec->Ability))
		{
			OutDescription = AuraAbility->GetDescription(AbilitySpec->Level);
			OutNextLevelDescription = AuraAbility->GetNextLevelDescription(AbilitySpec->Level + 1);
			return true;
		}
	}
	const UAbilityInfo* AbilityInfo = UAuraAbilitySystemLibrary::GetAbilityInfo(GetAvatarActor());
	if (!AbilityTag.IsValid() || AbilityTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_None))
	{
		OutDescription = FString();
	}
	else
	{
		OutDescription = UAuraGameplayAbility::GetLockedDescription(AbilityInfo->FindAbilityInfoForTag(AbilityTag).LevelRequirement);
	}
	OutNextLevelDescription = FString();
	return false;
}

 void UAuraAbilitySystemComponent::ClearSlot(FGameplayAbilitySpec* Spec) //相当于从ability中移除了inputTag
{
	 const FGameplayTag Slot = GetInputTagFromSpec(*Spec);
	Spec->DynamicAbilityTags.RemoveTag(Slot);
}

void UAuraAbilitySystemComponent::ClearAbilitiesOfSlot(const FGameplayTag& Slot)//有这个inputTag的ability，都移除这个inputTag
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (AbilityHasSlot(&Spec, Slot))
		{
			ClearSlot(&Spec);
		}
	}
}

bool UAuraAbilitySystemComponent::AbilityHasSlot(FGameplayAbilitySpec* Spec, const FGameplayTag& Slot)//这个ability是否有这个inputTag
{
	for (FGameplayTag Tag : Spec->DynamicAbilityTags)
	{
		if (Tag.MatchesTagExact(Slot))
		{
			return true;
		}
	}
	return false;
}

void UAuraAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	if(!bStartupAbilitiesGiven)
	{
		bStartupAbilitiesGiven=true;
		AbilitiesGivenDelegate.Broadcast();
	}
	
}

void UAuraAbilitySystemComponent::ClientUpdateAbilityStatus_Implementation(const FGameplayTag& AbilityTag,
	const FGameplayTag& StatusTag,int32 AbilityLevel)
{
	AbilityStatusChanged.Broadcast(AbilityTag,StatusTag,AbilityLevel);
}

void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                                     const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;

	EffectSpec.GetAllAssetTags(TagContainer); 

	EffectAssetTags.Broadcast(TagContainer);
	
}
