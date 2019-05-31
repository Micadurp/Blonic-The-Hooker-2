// Fill out your copyright notice in the Description page of Project Settings.


#include "Hooker.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UHooker::UHooker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHooker::BeginPlay()
{
	Super::BeginPlay();

	SetupInputComponent();
	SetupMovementComponent();
}

void UHooker::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Hook", IE_Pressed, this, &UHooker::Attach);
		InputComponent->BindAction("Hook", IE_Released, this, &UHooker::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}

void UHooker::SetupMovementComponent()
{
	CharacterMovementComponent = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();
	if (CharacterMovementComponent != nullptr)
	{
		//NOTHING
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing movement component"), *GetOwner()->GetName())
	}
}

void UHooker::Attach()
{
	FHitResult Hit = GetFirstBodyInReach();
	//UE_LOG(LogTemp, Error, TEXT("HOOKING TARGET: %s"), *Hit.GetActor()->GetName())
	HookHit = Hit;
}

void UHooker::Release()
{
	HookHit.Reset();
}

// Called every frame
void UHooker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (HookHit.GetActor() != nullptr) // There has gotta be a better check
	{
		DrawDebugLine(GetWorld(), GetReachLineStart(), HookHit.Location, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

		FVector Direction = HookHit.Location - GetOwner()->GetActorLocation();
		Direction.Normalize();

		if (CharacterMovementComponent != nullptr)
		{
			CharacterMovementComponent->AddImpulse(Direction * Speed, true);
		}
	}
}

FHitResult UHooker::GetFirstBodyInReach() const
{
	FHitResult Hit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	bool HitSomething = false;
	HitSomething = GetWorld()->LineTraceSingleByObjectType(Hit, GetReachLineStart(), GetReachLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic), TraceParameters);

	AActor* ActorHit = Hit.GetActor();

	if (HitSomething)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *ActorHit->GetName())
	}
	return Hit;
}

FVector UHooker::GetReachLineStart() const
{
	FVector ActorPosition;
	FRotator ActorRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ActorPosition, ActorRotation);

	return ActorPosition;
}

FVector UHooker::GetReachLineEnd() const
{
	FVector ActorPosition;
	FRotator ActorRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(ActorPosition, ActorRotation);

	return ActorPosition + (ActorRotation.Vector() * Reach);
}