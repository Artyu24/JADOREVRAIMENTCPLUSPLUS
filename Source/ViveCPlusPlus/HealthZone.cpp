// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthZone.h"
#include "Components/BoxComponent.h"
#include "ViveCPlusPlusCharacter.h"

// Sets default values
AHealthZone::AHealthZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);

	isInRange = false;

	//FComponentBeginOverlapSignature OnComponentBeginOverlap;
	//FComponentEndOverlapSignature OnComponentEndOverlap;
}

// Called when the game starts or when spawned
void AHealthZone::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AHealthZone::OnOverlapBegin);
	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &AHealthZone::OnOverlapEnd);

	if (isBad)
		changeHeal = -1;
	else
		changeHeal = 1;
}

// Called every frame
void AHealthZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	timer += DeltaTime;

	if(isInRange && timer >= 1)
	{
		timer = 0;
		Character->SetLife(changeHeal);
		GLog->Log("Health :  " + FString::FromInt(Character->GetLife()));
	}
}

void AHealthZone::OnOverlapBegin(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	isInRange = true;
	Character = Cast<AViveCPlusPlusCharacter>(OtherActor);
}

void AHealthZone::OnOverlapEnd(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherIndex)
{
	isInRange = false;
}