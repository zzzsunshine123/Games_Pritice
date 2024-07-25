// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocation()
{
	 const FVector Forward=GetAvatarActorFromActorInfo()->GetActorForwardVector();
	 const FVector Location=GetAvatarActorFromActorInfo()->GetActorLocation();
	 const float DeltaSpread=SpawnSpread/NumMinions;

	const FVector LeftOfSpread=Forward.RotateAngleAxis(-SpawnSpread/2.f,FVector::ZAxisVector);

	TArray<FVector>SpawnLocation;

	for(int32 i=0;i<NumMinions;i++)
	{
		const FVector Direction=LeftOfSpread.RotateAngleAxis(DeltaSpread*i,FVector::ZAxisVector);
		FVector ChosenSpawnLocation=Location+Direction*FMath::FRandRange(MinSpawnDistance,MaxSpawnDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit,ChosenSpawnLocation+FVector(0.f,0.f,400.f),ChosenSpawnLocation-FVector(0.f,0.f,400.f),ECC_Visibility);

		if(Hit.bBlockingHit)
		{
			ChosenSpawnLocation=Hit.ImpactPoint;
		}
		SpawnLocation.Add(ChosenSpawnLocation);
		
		 
	}
	return SpawnLocation;
	
}

TSubclassOf<APawn> UAuraSummonAbility::GetRandomMinionClass()
{
	int32 size=MinionClasses.Num();

	const int32 randomIndex=FMath::RandRange(0,size-1);
	return MinionClasses[randomIndex];
}
