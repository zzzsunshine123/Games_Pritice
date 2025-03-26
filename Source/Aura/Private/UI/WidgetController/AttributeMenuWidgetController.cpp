// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS=CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo)

     for(auto& Pair:AS->TagsToAttributes)
     {
     	BroadcastAttributeInfo(Pair.Key,Pair.Value());
     }

	
	AttributePointsDelegate.Broadcast(GetAuraPS()->GetAttributePoints());
	
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{


	GetAuraPS()->OnAttributePointsChangedDelegate.AddLambda(
  [this](int32 NewAttributePoint)
  {
	  AttributePointsDelegate.Broadcast(NewAttributePoint);
  }
  );
	check(AttributeInfo)
	for(auto& Pair:GetAuraAS()->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this,Pair](const FOnAttributeChangeData& Data)
		{

			BroadcastAttributeInfo(Pair.Key,Pair.Value());
	
		}
		
		);
	}
}

void UAttributeMenuWidgetController::UpGradeAttribute(const FGameplayTag& AttributeTag)
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	AuraASC->UpGradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
                                                            const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue=Attribute.GetNumericValue(AttributeSet);

	AttributeInfoDelegate.Broadcast(Info);
}
