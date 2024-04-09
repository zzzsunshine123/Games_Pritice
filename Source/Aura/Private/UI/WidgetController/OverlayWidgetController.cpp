// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include"UI/HUD/AuraHUD.h"
#include "AbilitySystem/AuraAttributeSet.h"
void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttribute= CastChecked<UAuraAttributeSet>(Attributes);

	OnHealthChanged.Broadcast(AuraAttribute->GetHealth());

	OnMaxHealthChanged.Broadcast(AuraAttribute->GetMaxHealth());

	OnManaChanged.Broadcast(AuraAttribute->GetMana());

	OnMaxManaChanged.Broadcast(AuraAttribute->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencoes()
{
	const UAuraAttributeSet* AuraAttribute= CastChecked<UAuraAttributeSet>(Attributes);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttribute->GetHealthAttribute()).AddUObject(this,&UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttribute->GetMaxHealthAttribute()).AddUObject(this,&UOverlayWidgetController::MaxHealthChanged);


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttribute->GetManaAttribute()).AddUObject(this,&UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttribute->GetMaxManaAttribute()).AddUObject(this,&UOverlayWidgetController::MaxManaChanged);

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(

	  [](const FGameplayTagContainer& AssetTags)
	  {
	  	for(const auto& tag:AssetTags)
	  	{
			 
			  const FString Msg = FString::Printf(TEXT("GE Tag: %s"),*tag.ToString());

			  GEngine->AddOnScreenDebugMessage(-1,8.f,FColor::Blue,Msg);
		  }
	  }
	);
	
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{

	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{

	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
