// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WIdgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{

	PlayerController =WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.Attributes;
}

void UAuraWidgetController::BroadcastInitialValues()
{

	
}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}
