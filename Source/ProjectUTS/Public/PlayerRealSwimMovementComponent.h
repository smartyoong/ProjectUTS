// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerRealSwimMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUTS_API UPlayerRealSwimMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
    // �Է� ó��
    void SetThrustInput(float Value);
    void SetVerticalInput(float Value);

    // ���� ���� ���� �������̵�
    virtual void PhysSwimming(float DeltaTime, int32 Iterations) override;

protected:
    // ���� ������
    //UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    //float Mass = 100.0f; // kg �̹� �θ� Ŭ�������� ���ǵ�

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float Volume = 0.1f; // m��

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float MaxThrust = 1000.0f; // N

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float MaxSpeed = 500.0f; // cm/s

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float DragCoefficient = 0.8f;

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float CrossSectionalArea = 1.0f; // m��

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float WaterDensity = 1027.0f; // kg/m��

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float Gravity = 9.81f;

private:
    float ThrustInput = 0.0f;
    float VerticalInput = 0.0f;
    FVector CurrentVelocity = FVector::ZeroVector;
};
