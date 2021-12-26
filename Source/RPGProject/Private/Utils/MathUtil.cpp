#include "Utils/MathUtil.h"

bool FUtils::GetAngleDirection(const FVector Vector, float& Angle)
{
	Angle = -1.0f;
	if (FMath::IsNearlyEqual(Vector.X, 1.0f) && FMath::IsNearlyZero(Vector.Y)) Angle = 0.0f;
	else if (FMath::IsNearlyEqual(Vector.X, 1.0f) && FMath::IsNearlyEqual(Vector.Y, 1.0f)) Angle = 45.0f;
	else if (FMath::IsNearlyZero(Vector.X) && FMath::IsNearlyEqual(Vector.Y, 1.0f)) Angle = 90.0f;
	else if (FMath::IsNearlyEqual(Vector.X, -1.0f) && FMath::IsNearlyEqual(Vector.Y, 1.0f)) Angle = 135.0f;
	else if (FMath::IsNearlyEqual(Vector.X, -1.0f) && FMath::IsNearlyZero(Vector.Y)) Angle = 180.0f;
	else if (FMath::IsNearlyEqual(Vector.X, -1.0f) && FMath::IsNearlyEqual(Vector.Y, -1.0f)) Angle = 225.0f;
	else if (FMath::IsNearlyZero(Vector.X) && FMath::IsNearlyEqual(Vector.Y, -1.0f)) Angle = 270.0f;
	else if (FMath::IsNearlyEqual(Vector.X, 1.0f) && FMath::IsNearlyEqual(Vector.Y, -1.0f)) Angle = 315.0f;
	return !FMath::IsNearlyEqual(Angle, -1.0f);
}

//Converts to angle between 0 and 360 degrees
float FUtils::NormalizeToCircleAngle(float Angle)
{
	Angle = Angle < 0.0f ? (360.0f + Angle) : Angle;
	Angle = Angle - FMath::TruncToFloat(Angle / 360.0f) * 360.0f;
	return Angle;
}

//Calculates the angle between vectors in radian
float FUtils::RadianBetweenVectors(const FVector& Vector1, const FVector& Vector2)
{
	return FMath::Acos(FVector::DotProduct(Vector1, Vector2));
}

//Calculates the angle between vectors in degrees
float FUtils::DegreesBetweenVectors(const FVector& Vector1, const FVector& Vector2)
{
	const auto CrossProduct = FVector::CrossProduct(Vector1, Vector2);
	auto Degrees = FMath::RadiansToDegrees(RadianBetweenVectors(Vector1, Vector2));
	Degrees = CrossProduct.IsZero() ? Degrees : FMath::Sign(CrossProduct.Z) * Degrees;
	return FMath::TruncToFloat(Degrees);
}
