// Fill out your copyright notice in the Description page of Project Settings.


#include "SwimMovementComponent.h"

USwimMovementComponent::USwimMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USwimMovementComponent::SetThrustInput(float Value)
{
	ThrustInput = FMath::Clamp(Value, -1.0f, 1.0f);
}

void USwimMovementComponent::SetVerticalInput(float Value)
{
	VerticalInput = FMath::Clamp(Value, -1.0f, 1.0f);
}

void USwimMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!PawnOwner || !UpdatedComponent) return;

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
    float VerticalForce = (BuoyancyForce - GravityForce) + (MaxThrust * VerticalInput * 0.5f); // Vertical 조작 힘
    NetForce += Up * VerticalForce;

    // 가속도 → 속도 → 이동
    FVector Acceleration = NetForce / Mass;
    CurrentVelocity += Acceleration * DeltaTime;
    CurrentVelocity = CurrentVelocity.GetClampedToMaxSize(MaxSpeed);

    FVector Delta = CurrentVelocity * DeltaTime;
    FHitResult Hit;
    SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentQuat(), true, Hit);

    if (Hit.IsValidBlockingHit())
    {
        SlideAlongSurface(Delta, 1.f - Hit.Time, Hit.Normal, Hit);
        CurrentVelocity = FVector::ZeroVector;
    }
}
