// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadSlot.h"
#include "MVVM_LoadScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlotSelected);
/**
 * 
 */
UCLASS()
class AURA_API UMVVM_LoadScreen : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	void InitializeLoadSlots();

	UPROPERTY(BlueprintAssignable)
	FSlotSelected SlotSelected;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadSlot> LoadSlotViewModelClass;

	UFUNCTION(BlueprintPure)
	UMVVM_LoadSlot* GetLoadSlotViewModelByIndex(int32 Index)const;

	UFUNCTION(BlueprintCallable)
	void NewSlotButtonPressed(int32 Slot,const FString& EnteredName);
	
	UFUNCTION(BlueprintCallable)
	void NewGameButtonPressed(int32 Slot);

	UFUNCTION(BlueprintCallable)
	void SelectSlotButtonPressed(int32 Slot);

	void SetNumLoadSlots(int32 InNumLoadSlots);

	int32 GetNumLoadSlots() const {return NumLoadSlots;}

	void LoadData();

	UFUNCTION(BlueprintCallable)
	void DeleteButtonPressed();

	UFUNCTION(BlueprintCallable)
	void PlayButtonPressed();
	
private:
	
	UPROPERTY()
	TMap<int32,UMVVM_LoadSlot*> LoadSlots;
	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot>LoadSlot_0;
	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot>LoadSlot_1;
	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot>LoadSlot_2;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot>SelectSlot;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,FieldNotify,Setter,Getter,meta=(AllowPrivateAccess="true"));
	int32 NumLoadSlots;
	
};

inline void UMVVM_LoadScreen::SetNumLoadSlots(int32 InNumLoadSlots)
{
	UE_MVVM_SET_PROPERTY_VALUE(NumLoadSlots,InNumLoadSlots);
}
