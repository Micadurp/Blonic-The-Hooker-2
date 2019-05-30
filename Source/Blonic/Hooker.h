// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Hooker.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLONIC_API UHooker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHooker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(EditAnywhere)
	float Reach = 10000.f;

	UPROPERTY(EditAnywhere)
	float Speed = 10.f;

	UCharacterMovementComponent* CharacterMovementComponent = nullptr;
	UInputComponent* InputComponent = nullptr;

	FHitResult HookHit;

	void SetupInputComponent();
	void SetupMovementComponent();
	void Attach();
	void Release();
	FHitResult GetFirstBodyInReach() const;
	FVector GetReachLineStart() const;
	FVector GetReachLineEnd() const;
};
