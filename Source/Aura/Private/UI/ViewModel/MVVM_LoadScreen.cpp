// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModel/MVVM_LoadScreen.h"

#include "Game/AuraGameInstance.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UMVVM_LoadScreen::InitializeLoadSlots()
{
	LoadSlot_0=NewObject<UMVVM_LoadSlot>(this,LoadSlotViewModelClass);
	LoadSlot_0->SetLoadSlotName("LoadSlot_0");
	LoadSlot_0->SlotIndex=0;
	LoadSlots.Add(0,LoadSlot_0);
	LoadSlot_1=NewObject<UMVVM_LoadSlot>(this,LoadSlotViewModelClass);
	LoadSlot_1->SetLoadSlotName("LoadSlot_1");
	LoadSlot_1->SlotIndex=1;
	LoadSlots.Add(1,LoadSlot_1);
	LoadSlot_2=NewObject<UMVVM_LoadSlot>(this,LoadSlotViewModelClass);
	LoadSlot_2->SetLoadSlotName("LoadSlot_2");
	LoadSlot_2->SlotIndex=2;
	LoadSlots.Add(2,LoadSlot_2);

	SetNumLoadSlots(LoadSlots.Num());
}

UMVVM_LoadSlot* UMVVM_LoadScreen::GetLoadSlotViewModelByIndex(int32 Index) const
{
	return LoadSlots.FindChecked(Index);
}

void UMVVM_LoadScreen::NewSlotButtonPressed(int32 Slot, const FString& EnteredName)
{
	AAuraGameModeBase* AuraGameModeBase = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));

	LoadSlots[Slot]->SetMapName(AuraGameModeBase->DefaultMapName);
	LoadSlots[Slot]->SetPlayerName(EnteredName);
	LoadSlots[Slot]->SlotStatus=Taken;
	LoadSlots[Slot]->PlayerStartTag=AuraGameModeBase->DefaultPlayerStartTag;
	AuraGameModeBase->SaveSlotData(LoadSlots[Slot],Slot);

	LoadSlots[Slot]->InitializeSlot();


	UAuraGameInstance* AuraGameInstance = Cast<UAuraGameInstance>(AuraGameModeBase->GetGameInstance());

	AuraGameInstance->LoadSlotName=LoadSlots[Slot]->GetLoadSlotName();
	AuraGameInstance->LoadSlotIndex=LoadSlots[Slot]->SlotIndex;
	AuraGameInstance->PlayerStartTag=AuraGameModeBase->DefaultPlayerStartTag;
	
}

void UMVVM_LoadScreen::NewGameButtonPressed(int32 Slot)
{
	LoadSlots[Slot]->SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadScreen::SelectSlotButtonPressed(int32 Slot)
{
	SlotSelected.Broadcast();
	for(auto LoadSlot:LoadSlots)
	{
		if(LoadSlot.Key==Slot)
		{
			LoadSlot.Value->EnableSelectSlotButton.Broadcast(false);
		}
		else
		{
			LoadSlot.Value->EnableSelectSlotButton.Broadcast(true);
		}
	}
	SelectSlot=LoadSlots[Slot];
}

void UMVVM_LoadScreen::LoadData()
{
	AAuraGameModeBase* AuraGameMode=Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
	for(auto LoadSlot:LoadSlots)
	{
		ULoadScreenSaveGame* SaveObject =AuraGameMode->GetSaveSlotData(LoadSlot.Value->GetLoadSlotName(),LoadSlot.Key);

		const FString PlayerName=SaveObject->PlayerName;
		const FString MapName=SaveObject->MapName;

		TEnumAsByte<ESaveSlotStatus> SaveSlotStatus =SaveObject->SaveSlotStatus;

		LoadSlot.Value->SlotStatus=SaveSlotStatus;
		LoadSlot.Value->SetPlayerName(PlayerName);
		LoadSlot.Value->SetMapName(MapName);
		LoadSlot.Value->InitializeSlot();
		LoadSlot.Value->PlayerStartTag=SaveObject->PlayerStartTag;
	}
}

void UMVVM_LoadScreen::DeleteButtonPressed()
{

	if(IsValid(SelectSlot))
	{
		AAuraGameModeBase::DeleteSlot(SelectSlot->GetLoadSlotName(),SelectSlot->SlotIndex);
		SelectSlot->SlotStatus=Vacant;
		SelectSlot->InitializeSlot();
		SelectSlot->EnableSelectSlotButton.Broadcast(true);
	}
	
}

void UMVVM_LoadScreen::PlayButtonPressed()
{
	
	AAuraGameModeBase* AuraGameMode=Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));

	UAuraGameInstance* AuraGameInstance=Cast<UAuraGameInstance>(AuraGameMode->GetGameInstance());
	AuraGameInstance->PlayerStartTag=SelectSlot->PlayerStartTag;
	AuraGameInstance->LoadSlotName=SelectSlot->GetLoadSlotName();
	AuraGameInstance->LoadSlotIndex=SelectSlot->SlotIndex;
	
	if(IsValid(SelectSlot))
	{
		AuraGameMode->TravelToMap(SelectSlot);
	}
	
}
