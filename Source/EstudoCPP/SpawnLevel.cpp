// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnLevel.h"

#include "BaseLevel.h"
#include "Engine.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnLevel::ASpawnLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnLevel::BeginPlay()
{
	Super::BeginPlay();

	// Gera os 4 primeiros levels
	SpawnLevel(true);
	SpawnLevel(false);
	
}

// Called every frame
void ASpawnLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/* TUTORIAL */

// Cria um novo level a medida q o jogador avanca no jogo
void ASpawnLevel::SpawnLevel(bool IsFirst)
{
	// O tamanho de cada level, no eixo Y, eh 1000
	SpawnLocation = FVector(0.0f, 1000.f, 0.0f);
	SpawnRotation = FRotator(0, 90, 0);

	// Se NAO for o primeiro level, vai pegar a posicao do "SpawnLocation" do ultimo nivel
	if (!IsFirst) {
		ABaseLevel* LastLevel = LevelList.Last();
		SpawnLocation = LastLevel->GetSpawnLocation()->GetComponentTransform().GetTranslation();
	}

	// Cria Aleatoriamente o proximo level
	RandomLevel = FMath::RandRange(1, 5);
	ABaseLevel* NewLevel = nullptr;

	switch (RandomLevel) {
	case 1:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level1, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 2:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level2, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 3:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level3, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 4:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level4, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 5:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level5, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	default:
		break;
	}

	if (NewLevel) {
		if (NewLevel->GetTrigger()) {
			NewLevel->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ASpawnLevel::OnOverlapBegin);
		}
	}

	LevelList.Add(NewLevel);
	if (LevelList.Num() > 5) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *LevelList[0]->GetName()));
		LevelList[0]->Destroy();
		LevelList.RemoveAt(0);
	}

}

void ASpawnLevel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherAcoter, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnLevel(false);
}

