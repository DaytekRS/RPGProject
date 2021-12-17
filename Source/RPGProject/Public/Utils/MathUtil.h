#pragma once
namespace FUtils
{
	float GetAngleDirection(const FVector& MoveVector);
	float NormalizeToCircleAngle(const float Angle);
	float RadianBetweenVectors(const FVector& Vector1, const FVector& Vector2);
	float DegreesBetweenVectors(const FVector& Vector1, const FVector& Vector2);
}
