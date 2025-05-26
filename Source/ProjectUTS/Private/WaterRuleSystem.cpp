// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterRuleSystem.h"

float UWaterRuleSystem::GetPressureAtDepth(float Depth) const
{
    // P = P0 + ρgh
    return SurfacePressure + (WaterDensity * Gravity * Depth);
}

float UWaterRuleSystem::GetTemperatureAtDepth(float Depth) const
{
    float Temperature = SurfaceTemperature;

    if (Depth <= 200.0f)
    {
        // 표면층: 0 ~ 200m 구간에서는 서서히 감소
        Temperature = FMath::Lerp(SurfaceTemperature, ShallowTemperatureAt200m, Depth / 200.0f);
    }
    else if (Depth <= 1000.0f && Depth > 200.0f)
    {
        // 수온약층 (Thermocline): 200 ~ 1000m 구간에서 급격히 감소
        Temperature = FMath::Lerp(ShallowTemperatureAt200m, DeepOceanTemperature, (Depth - 200.0f) / (1000.0f - 200.0f));
    }
	else if (Depth > 1000.0f && Depth <= 4000)
    {
        // 심해층: 1000m 이상의 깊이에서는 거의 일정한 온도 유지
        Temperature = FMath::Lerp(DeepOceanTemperature, MinimumOceanTemperature, Depth / 4000.0f);
    }
    else
    {
		Temperature = MinimumOceanTemperature; // 4000m 이상의 깊이에서는 최소 온도 유지
    }

    return Temperature;
}

float UWaterRuleSystem::GetLightIntensityAtDepth(float Depth) const
{
    // 빛 감쇠 모델: I = I0 * e^(-k * d)
    // I0 = 1.0 (100% 밝기 기준)
    return FMath::Clamp(FMath::Exp(-LightAttenuationCoefficient * Depth), 0.0f, 1.0f);
}
