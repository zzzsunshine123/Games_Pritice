// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/SaveGame.h"
#include "UI/ViewModel/MVVM_LoadSlot.h"
#include "AuraGameModeBase.generated.h"
class UCharacterClassInfo;
class UAbilityInfo;
/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly,Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfo>CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly,Category="AbilityInfo")
	TObjectPtr<UAbilityInfo>AbilityInfo;


	void SaveSlotData(UMVVM_LoadSlot* LoadSlot,int32 SlotIndex);

	static void DeleteSlot(FString SlotName,int32 SlotIndex);

	void TravelToMap(UMVVM_LoadSlot* Slot);
	
    ULoadScreenSaveGame* GetSaveSlotData(const FString& SlotName,int32 SlotIndex)const;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame>LoadScreenSaveGameClass;

	UPROPERTY(EditDefaultsOnly)
	FString DefaultMapName;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DefaultMap;

	UPROPERTY(EditDefaultsOnly)
	FName DefaultPlayerStartTag;

	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
protected:
	void BeginPlay() override;

	
};
