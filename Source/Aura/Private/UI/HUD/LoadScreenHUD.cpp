// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/LoadScreenHUD.h"

#include "Blueprint/UserWidget.h"

void ALoadScreenHUD::BeginPlay()
{
	Super::BeginPlay();

	LoadScreenViewModel=NewObject<UMVVM_LoadScreen>(this,LoadScreenViewModelClass);
	LoadScreenViewModel->InitializeLoadSlots();
	
	LoadScreenWidget=CreateWidget<ULoadScreenWidget>(GetWorld(),LoadScreenWidgetClass);
	LoadScreenWidget->AddToViewport();
	LoadScreenWidget->BlueprintInitializeWidget();

	LoadScreenViewModel->LoadData();
}
