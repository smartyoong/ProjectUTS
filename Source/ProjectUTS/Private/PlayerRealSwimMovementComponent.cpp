// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRealSwimMovementComponent.h"

void UPlayerRealSwimMovementComponent::SetThrustInput(float Value)
{
    ThrustInput = FMath::Clamp(Value, -1.0f, 1.0f);
}

void UPlayerRealSwimMovementComponent::SetVerticalInput(float Value)
{
    VerticalInput = FMath::Clamp(Value, -1.0f, 1.0f);
}

void UPlayerRealSwimMovementComponent::PhysSwimming(float DeltaTime, int32 Iterations)
{
    if (!CharacterOwner || !UpdatedComponent)
        return;

    const FVector Forward = UpdatedComponent->GetForwardVector();
    const FVector Up = FVector::UpVector;
    const float Speed = CurrentVelocity.Size();

    // 힘 계산
    float GravityForce = Mass * Gravity;
    float BuoyancyForce = WaterDensity * Volume * Gravity;

    float DragForce = 0.5f * DragCoefficient * WaterDensity * CrossSectionalArea * FMath::Square(Speed / 100.f); // v in m/s
    float ThrustForce = MaxThrust * ThrustInput;

    // 방향별 힘 분해
    FVector NetForce = FVector::ZeroVector;

    // 전진: 추진력 - 항력
    NetForce += Forward * ThrustForce;
    if (Speed > KINDA_SMALL_NUMBER)
    {
        NetForce += -CurrentVelocity.GetSafeNormal() * DragForce;
    }

    // 수직: 부력 - 중력 + 수직입력
    float VerticalForce = (BuoyancyForce - GravityForce) + (MaxThrust * VerticalInput * 0.5f);
    NetForce += Up * VerticalForce;

    // 가속도 → 속도 → 이동
    FVector ComputedAcceleration = NetForce / Mass;
    CurrentVelocity += ComputedAcceleration * DeltaTime;
    CurrentVelocity = CurrentVelocity.GetClampedToMaxSize(MaxSpeed);

    FVector Delta = CurrentVelocity * DeltaTime;

    FHitResult Hit;
    SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentQuat(), true, Hit);

    if (Hit.IsValidBlockingHit())
    {
        SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit, true);
        CurrentVelocity = FVector::ZeroVector;
    }

    // Velocity를 엔진에도 반영해줘야 네트워크/기타 기능과 연동됨
    Velocity = CurrentVelocity;
}