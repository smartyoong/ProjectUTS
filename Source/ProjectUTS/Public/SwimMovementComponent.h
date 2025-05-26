// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "SwimMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUTS_API USwimMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
    // 환경 상수
    UPROPERTY(EditAnywhere, Category = "Physics|Environment")
    float WaterDensity = 1027.0f; // kg/m³

    UPROPERTY(EditAnywhere, Category = "Physics|Environment")
    float Gravity = 9.81f;

    // 대상 특성
    UPROPERTY(EditAnywhere, Category = "Physics|Object")
    float Mass = 100.0f; // kg

    UPROPERTY(EditAnywhere, Category = "Physics|Object")
    float Volume = 0.1f; // m³ (사람 = 0.07 ~ 0.1)

    UPROPERTY(EditAnywhere, Category = "Physics|Object")
    float DragCoefficient = 0.8f;

    UPROPERTY(EditAnywhere, Category = "Physics|Object")
    float CrossSectionalArea = 1.0f; // m²

    UPROPERTY(EditAnywhere, Category = "Physics|Thrust")
    float MaxThrust = 1000.0f; // N (발차기 or 엔진)

    UPROPERTY(EditAnywhere, Category = "Physics|Limits")
    float MaxSpeed = 500.0f; // cm/s

    // 현재 속도
    FVector CurrentVelocity = FVector::ZeroVector;

    // 입력
    float ThrustInput = 0.0f;    // 전후
    float VerticalInput = 0.0f;  // 잠수/부상

public:
    USwimMovementComponent();

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetThrustInput(float Value);     // -1 ~ +1
    void SetVerticalInput(float Value);   // -1 ~ +1 (잠수/부상)
	
};
