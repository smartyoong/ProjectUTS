// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WaterRuleSystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUTS_API UWaterRuleSystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = "Environment Constants")
    float WaterDensity = 1027.0f; // kg/m��

    UPROPERTY(EditDefaultsOnly, Category = "Environment Constants")
    float SurfacePressure = 101325.0f; // Pa

    UPROPERTY(EditDefaultsOnly, Category = "Environment Constants")
    float Gravity = 9.81f; // m/s��

    UPROPERTY(EditDefaultsOnly, Category = "Environment Constants")
    float SurfaceTemperature = 20.0f; // ��C

    UPROPERTY(EditDefaultsOnly, Category = "Environment Constants")
    float ShallowTemperatureAt200m = 18.0f; // ǥ���� ��(200m)������ �µ�

    UPROPERTY(EditDefaultsOnly, Category = "Environment Constants")
    float DeepOceanTemperature = 4.0f;      // ������ �µ� (1000m �̻�)

    UPROPERTY(EditDefaultsOnly, Category = "Environment Constants")
	float MinimumOceanTemperature = 0.0f; // �ּ� �ؾ� �µ� (0��C)

    UPROPERTY(EditDefaultsOnly, Category = "Environment Constants")
    float LightAttenuationCoefficient = 0.045f; // per meter

	UPROPERTY(EditDefaultsOnly, Category = "Environment Constants")
	float WaterViscosity = 0.001f; // Pa��s ���� ����

    // ȯ�� ���� �Լ�
    UFUNCTION(BlueprintCallable, Category = "Environment")
    float GetPressureAtDepth(float Depth) const;

    UFUNCTION(BlueprintCallable, Category = "Environment")
    float GetTemperatureAtDepth(float Depth) const;

    UFUNCTION(BlueprintCallable, Category = "Environment")
    float GetLightIntensityAtDepth(float Depth) const;
};
