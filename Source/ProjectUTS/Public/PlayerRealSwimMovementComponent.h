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
    // 입력 처리
    void SetThrustInput(float Value);
    void SetVerticalInput(float Value);

    // 실제 수영 로직 오버라이드
    virtual void PhysSwimming(float DeltaTime, int32 Iterations) override;

protected:
    // 물리 설정값
    //UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    //float Mass = 100.0f; // kg 이미 부모 클래스에서 정의됨

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float Volume = 0.1f; // m³

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float MaxThrust = 1000.0f; // N

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float MaxSpeed = 500.0f; // cm/s

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float DragCoefficient = 0.8f;

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float CrossSectionalArea = 1.0f; // m²

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float WaterDensity = 1027.0f; // kg/m³

    UPROPERTY(EditAnywhere, Category = "Underwater Physics")
    float Gravity = 9.81f;

private:
    float ThrustInput = 0.0f;
    float VerticalInput = 0.0f;
    FVector CurrentVelocity = FVector::ZeroVector;
};
