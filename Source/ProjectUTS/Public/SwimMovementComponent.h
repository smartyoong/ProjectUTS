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
    // ȯ�� ���
    UPROPERTY(EditAnywhere, Category = "Physics|Environment")
    float WaterDensity = 1027.0f; // kg/m��

    UPROPERTY(EditAnywhere, Category = "Physics|Environment")
    float Gravity = 9.81f;

    // ��� Ư��
    UPROPERTY(EditAnywhere, Category = "Physics|Object")
    float Mass = 100.0f; // kg

    UPROPERTY(EditAnywhere, Category = "Physics|Object")
    float Volume = 0.1f; // m�� (��� = 0.07 ~ 0.1)

    UPROPERTY(EditAnywhere, Category = "Physics|Object")
    float DragCoefficient = 0.8f;

    UPROPERTY(EditAnywhere, Category = "Physics|Object")
    float CrossSectionalArea = 1.0f; // m��

    UPROPERTY(EditAnywhere, Category = "Physics|Thrust")
    float MaxThrust = 1000.0f; // N (������ or ����)

    UPROPERTY(EditAnywhere, Category = "Physics|Limits")
    float MaxSpeed = 500.0f; // cm/s

    // ���� �ӵ�
    FVector CurrentVelocity = FVector::ZeroVector;

    // �Է�
    float ThrustInput = 0.0f;    // ����
    float VerticalInput = 0.0f;  // ���/�λ�

public:
    USwimMovementComponent();

    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetThrustInput(float Value);     // -1 ~ +1
    void SetVerticalInput(float Value);   // -1 ~ +1 (���/�λ�)
	
};
