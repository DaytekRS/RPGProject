#pragma once
namespace FUtils
{
	bool GetAngleDirection(const FVector MoveVector, float& Angle);
	float NormalizeToCircleAngle(const float Angle);
	float RadianBetweenVectors(const FVector& Vector1, const FVector& Vector2);
	float DegreesBetweenVectors(const FVector& Vector1, const FVector& Vector2);
}
