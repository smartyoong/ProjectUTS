// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterRuleSystem.h"

float UWaterRuleSystem::GetPressureAtDepth(float Depth) const
{
    // P = P0 + ��gh
    return SurfacePressure + (WaterDensity * Gravity * Depth);
}

float UWaterRuleSystem::GetTemperatureAtDepth(float Depth) const
{
    float Temperature = SurfaceTemperature;

    if (Depth <= 200.0f)
    {
        // ǥ����: 0 ~ 200m ���������� ������ ����
        Temperature = FMath::Lerp(SurfaceTemperature, ShallowTemperatureAt200m, Depth / 200.0f);
    }
    else if (Depth <= 1000.0f && Depth > 200.0f)
    {
        // ���¾��� (Thermocline): 200 ~ 1000m �������� �ް��� ����
        Temperature = FMath::Lerp(ShallowTemperatureAt200m, DeepOceanTemperature, (Depth - 200.0f) / (1000.0f - 200.0f));
    }
	else if (Depth > 1000.0f && Depth <= 4000)
    {
        // ������: 1000m �̻��� ���̿����� ���� ������ �µ� ����
        Temperature = FMath::Lerp(DeepOceanTemperature, MinimumOceanTemperature, Depth / 4000.0f);
    }
    else
    {
		Temperature = MinimumOceanTemperature; // 4000m �̻��� ���̿����� �ּ� �µ� ����
    }

    return Temperature;
}

float UWaterRuleSystem::GetLightIntensityAtDepth(float Depth) const
{
    // �� ���� ��: I = I0 * e^(-k * d)
    // I0 = 1.0 (100% ��� ����)
    return FMath::Clamp(FMath::Exp(-LightAttenuationCoefficient * Depth), 0.0f, 1.0f);
}
