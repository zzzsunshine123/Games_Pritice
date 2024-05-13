// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine)
  UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);

	return *AuraAssetManager;
	
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
