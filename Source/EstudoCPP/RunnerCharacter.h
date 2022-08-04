// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunnerCharacter.generated.h"

UCLASS()
class ESTUDOCPP_API ARunnerCharacter : public ACharacter
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere)
		// O mesmo q fazer o '#include' do Camera Component, a diferenca eh q nao vai trazer os includes do proprio Camera Component
		class UCameraComponent* SideViewCamera;

public:
	// Sets default values for this character's properties
	ARunnerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

/* TUTORIAL */

protected:
	
	// Movimento do personagem
	void MoveRight(float value);

public:
	
	// Visao Lateral
	class UCameraComponent* GetSideViewCameraComponent() const
	{
		return SideViewCamera;
	}

	// Reseta a fase ao perder
	void RestartLevel();

	// Overlap da parede e dos espinhos
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
			AActor* OtherAcoter, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	float zPosition;
	FVector tempPos = FVector();

	bool CanMove;
};
