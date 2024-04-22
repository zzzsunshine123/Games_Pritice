// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS=CastChecked<UAuraAttributeSet>(Attributes);

	check(AttributeInfo)

     for(auto& Pair:AS->TagsToAttributes)
     {
	     FAuraAttributeInfo Info =AttributeInfo->FindAttributeInfoForTag(Pair.Key);
     	Info.AttributeValue = Pair.Value().GetNumericValue(AS);
     	AttributeInfoDelegate.Broadcast(Info);
     }
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}
