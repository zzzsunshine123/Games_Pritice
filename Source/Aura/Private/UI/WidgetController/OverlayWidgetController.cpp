// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include"UI/HUD/AuraHUD.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttribute= CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttribute->GetHealth());

	OnMaxHealthChanged.Broadcast(AuraAttribute->GetMaxHealth());

	OnManaChanged.Broadcast(AuraAttribute->GetMana());

	OnMaxManaChanged.Broadcast(AuraAttribute->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{

	AAuraPlayerState* AuraPlayerState=CastChecked<AAuraPlayerState>(PlayerState);

	AuraPlayerState->OnXPChangedDelegate.AddUObject(this,&UOverlayWidgetController::OnXPChanged);

	AuraPlayerState->OnLevelChangedDelegate.AddLambda(
      [this](int32 Newlevel)
      {
	      OnPlayerLevelChangedDelegate.Broadcast(Newlevel);
      }

	);
	const UAuraAttributeSet* AuraAttribute= CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttribute->GetHealthAttribute()).AddLambda(
     [this](const FOnAttributeChangeData& Data)
     {
     	OnHealthChanged.Broadcast(Data.NewValue);
     }
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttribute->GetMaxHealthAttribute()).AddLambda(
 [this](const FOnAttributeChangeData& Data)
  {
	 OnMaxHealthChanged.Broadcast(Data.NewValue);
  }
  );

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttribute->GetManaAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
  {
	OnManaChanged.Broadcast(Data.NewValue);
  }
  );

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttribute->GetMaxManaAttribute()).AddLambda(
[this](const FOnAttributeChangeData& Data)
  {
    OnMaxManaChanged.Broadcast(Data.NewValue);
  }
  );
	if(UAuraAbilitySystemComponent* AuraASC=Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		if(AuraASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(AuraASC);
		}
		else
		{
			AuraASC->AbilitiesGivenDelegate.AddUObject(this,& UOverlayWidgetController::OnInitializeStartupAbilities);
		}
		
		AuraASC->EffectAssetTags.AddLambda(
  [this](const FGameplayTagContainer& AssetTags)
  {
	  for(const auto& tag:AssetTags)
	  {
			 
		  FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
		   if(tag.MatchesTag(MessageTag))
		   {
			   const FUIWidgetRow* Row=GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable,tag);
			   MessageWidgetRowDelegate.Broadcast(*Row);
		   }
	  }
  }
);
	}


	
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UAuraAbilitySystemComponent* AuraASC)
{
	   if(!AuraASC->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;

	BroadcastDelegate.BindLambda([this,AuraASC](const FGameplayAbilitySpec& AbilitySpec)
	{
		FAuraAbilityInfo Info=AbilityInfo->FindAbilityInfoForTag(AuraASC->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag=AuraASC->GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});

	AuraASC->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP)
{
	const AAuraPlayerState* AuraPlayerState=CastChecked<AAuraPlayerState>(PlayerState);

	const  ULevelUpInfo* LevelUpInfo =AuraPlayerState->LevelUpInfo;

	checkf(LevelUpInfo,TEXT("Unable to find LevelUpInfo, Please fill out AuraPlayerState Blueprint"));

	const int32 Level=LevelUpInfo->FindLevelForXP(NewXP);  //下标0表示等级1

	const int32 MaxLevel=LevelUpInfo->LevelUpInfos.Num();//下标从0开始

	if(Level<=MaxLevel&&Level>=1)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInfos[Level-1].LevelUpRequirement;//等级1 对应info数组下标0
		 int32 PreviousLevelUpRequirement=0;//等级为1，对应infos[0]，没有previousInfo 所以设置为0
		if(Level>1)
		{
			PreviousLevelUpRequirement = LevelUpInfo->LevelUpInfos[Level - 2].LevelUpRequirement;
		}
		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);

		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
	
}


