// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/ShooterCharacter.h"
#include "imgui.h"
#include "ShooterCharacterWithGui.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AShooterCharacterWithGui : public AShooterCharacter
{
	GENERATED_BODY()
protected:
	virtual void Tick(float DeltaSeconds) override;
};
