// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include"UI/HUD/AuraHUD.h"
#include "AbilitySystem/AuraAttributeSet.h"
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
	

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(

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


