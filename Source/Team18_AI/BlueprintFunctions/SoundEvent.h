// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SoundEvent.generated.h"

class UTAListeneningComponent;

USTRUCT(BlueprintType)
struct FSoundEventData
{
	GENERATED_USTRUCT_BODY();
	
public:	
	UPROPERTY(BlueprintReadWrite)
	AActor* Instigator;
	
	UPROPERTY(BlueprintReadWrite)
	FVector Location = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	float LifeTime = 1.0f;

	UPROPERTY(BlueprintReadWrite)
	float Growth = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	float Radius = 0.0f;
	
	UPROPERTY(BlueprintReadWrite)
	bool bDebugDraw = false;
	
	TArray<UTAListeneningComponent*> ListenersHeard;
};

UCLASS()
class TEAM18_AI_API USoundEvent : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, meta=(DistplayName = "Spawn Sound Event", CompactTitle = "SpawnSound", Category = "Custom"))
	static void SpawnSoundEvent(FSoundEventData SoundEvent);
};
