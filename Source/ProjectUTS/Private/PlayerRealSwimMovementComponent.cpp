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

    // �� ���
    float GravityForce = Mass * Gravity;
    float BuoyancyForce = WaterDensity * Volume * Gravity;

    float DragForce = 0.5f * DragCoefficient * WaterDensity * CrossSectionalArea * FMath::Square(Speed / 100.f); // v in m/s
    float ThrustForce = MaxThrust * ThrustInput;

    // ���⺰ �� ����
    FVector NetForce = FVector::ZeroVector;

    // ����: ������ - �׷�
    NetForce += Forward * ThrustForce;
    if (Speed > KINDA_SMALL_NUMBER)
    {
        NetForce += -CurrentVelocity.GetSafeNormal() * DragForce;
    }

    // ����: �η� - �߷� + �����Է�
    float VerticalForce = (BuoyancyForce - GravityForce) + (MaxThrust * VerticalInput * 0.5f);
    NetForce += Up * VerticalForce;

    // ���ӵ� �� �ӵ� �� �̵�
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

    // Velocity�� �������� �ݿ������ ��Ʈ��ũ/��Ÿ ��ɰ� ������
    Velocity = CurrentVelocity;
}