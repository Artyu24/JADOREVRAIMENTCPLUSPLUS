// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpPad.h"

#include "ViveCPlusPlusCharacter.h"

// Sets default values
AJumpPad::AJumpPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void AJumpPad::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnComponentHit.AddDynamic(this, &AJumpPad::OnHit);
}

// Called every frame
void AJumpPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJumpPad::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AViveCPlusPlusCharacter* Character = Cast<AViveCPlusPlusCharacter>(OtherActor);
	if (Character == nullptr)
		return;

	Character->LaunchCharacter(FVector(0, 0, 1000), false, true);
}

