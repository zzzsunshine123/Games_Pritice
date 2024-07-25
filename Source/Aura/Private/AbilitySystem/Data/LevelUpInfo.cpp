// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	const int num=LevelUpInfos.Num();
	for(int i=0;i<num;i++)
	{
		if(XP<LevelUpInfos[i].LevelUpRequirement)
		{
			return i+1;
		}
	}
	return -1;
}
