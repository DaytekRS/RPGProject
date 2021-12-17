#include "Utils/MathUtil.h"

float FUtils::GetAngleDirection(const FVector& Vector)
{
	if (FMath::IsNearlyEqual(Vector.X, 1.0f) && FMath::IsNearlyZero(Vector.Y)) return 0;
	if (FMath::IsNearlyEqual(Vector.X, 1.0f) && FMath::IsNearlyEqual(Vector.Y, 1.0f)) return 45;
	if (FMath::IsNearlyZero(Vector.X) && FMath::IsNearlyEqual(Vector.Y, 1.0f)) return 90;
	if (FMath::IsNearlyEqual(Vector.X, -1.0f) && FMath::IsNearlyEqual(Vector.Y, 1.0f)) return 135;
	if (FMath::IsNearlyEqual(Vector.X, -1.0f) && FMath::IsNearlyZero(Vector.Y)) return 180;
	if (FMath::IsNearlyEqual(Vector.X, -1.0f) && FMath::IsNearlyEqual(Vector.Y, -1.0f)) return 225;
	if (FMath::IsNearlyZero(Vector.X) && FMath::IsNearlyEqual(Vector.Y, -1.0f)) return 270;
	if (FMath::IsNearlyEqual(Vector.X, 1.0f) && FMath::IsNearlyEqual(Vector.Y, -1.0f)) return 315;
	return -1;
}

float FUtils::NormalizeToCircleAngle(float Angle)
{
	Angle = Angle < 0.0f ? (360.0f + Angle) : Angle;
	Angle = Angle - FMath::TruncToFloat(Angle / 360.0f) * 360.0f;
	return Angle;
}

float FUtils::RadianBetweenVectors(const FVector& Vector1, const FVector& Vector2)
{
	return FMath::Acos(FVector::DotProduct(Vector1, Vector2));
}

float FUtils::DegreesBetweenVectors(const FVector& Vector1, const FVector& Vector2)
{
	const auto CrossProduct = FVector::CrossProduct(Vector1, Vector2);
	auto Degrees = FMath::RadiansToDegrees(RadianBetweenVectors(Vector1, Vector2));
	Degrees = CrossProduct.IsZero() ? Degrees : FMath::Sign(CrossProduct.Z) * Degrees;
	return FMath::TruncToFloat(Degrees);
}
