#include "Player/RPGBaseCharacter.h"

#include "DrawDebugHelpers.h"
#include "InteractiveInterface.h"
#include "Camera/CameraComponent.h"
#include "Components/RPGCharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Utils/MathUtil.h"
#include "Components/RPGHealthComponent.h"
#include "Components/RPGWeaponComponent.h"

ARPGBaseCharacter::ARPGBaseCharacter(const FObjectInitializer& ObjInit) : Super(
	ObjInit.SetDefaultSubobjectClass<URPGCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SocketOffset = FVector(0.0f, 0.0f, 80.0f);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HeathComponent = CreateDefaultSubobject<URPGHealthComponent>("HeathComponent");
	HeathComponent->OnDeath.AddUObject(this, &ARPGBaseCharacter::OnDeath);

	WeaponComponent = CreateDefaultSubobject<URPGWeaponComponent>("WeaponComponent");
}

void ARPGBaseCharacter::EquipWeapon(ARPGBaseWeapon* Weapon) const
{
	WeaponComponent->EquipWeapon(Cast<ARPGBaseWeapon>(FoundInteractiveObject));
}

void ARPGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(SpringArmComponent);
	check(CameraComponent);
	check(HeathComponent);
	check(WeaponComponent);

	LandedDelegate.AddDynamic(this, &ARPGBaseCharacter::OnGroundLanded);
	if (NeedSearchInteractive) GetWorld()->GetTimerManager().SetTimer(SearchInteractiveTimer, this, &ARPGBaseCharacter::SearchInteractive, SearchInteractiveRate, true);
	if (NeedRotateMesh) GetWorld()->GetTimerManager().SetTimer(RotateTimer, this, &ARPGBaseCharacter::RotateToMovement, RateRotateMesh, true);
}

void ARPGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARPGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARPGBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARPGBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ARPGBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &ARPGBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARPGBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ARPGBaseCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ARPGBaseCharacter::StopRun);
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ARPGBaseCharacter::StartInteractive);
}

bool ARPGBaseCharacter::GetInteractiveData(FInteractiveData& InteractiveData)
{
	if (!FoundInteractiveObject) return false;
	InteractiveData = FoundInteractiveObject->GetInteractiveData();
	return true;
}

void ARPGBaseCharacter::MoveForward(const float Axis)
{
	FVector CameraVector = CameraComponent->GetForwardVector().GetSafeNormal2D();
	MoveVector.X = Axis;
	AddMovementInput(CameraVector, Axis);
}

void ARPGBaseCharacter::MoveRight(const float Axis)
{
	MoveVector.Y = Axis;
	AddMovementInput(CameraComponent->GetRightVector(), Axis);
}

void ARPGBaseCharacter::RotateToMovement()
{
	if (GetMovementComponent()->IsFalling()) return;

	//DirectionAngle - Angle between Move Vector and Forward Vector camera
	float DirectionAngle;
	if (!FUtils::GetAngleDirection(MoveVector, DirectionAngle)) return;

	FVector CameraVector = CameraComponent->GetForwardVector().GetSafeNormal2D();
	//RotateMeshAngle - Angle between Mesh Forward Vector and Forward Vector camera
	float RotateMeshAngle = FUtils::DegreesBetweenVectors(CameraVector, GetMesh()->GetRightVector());
	RotateMeshAngle = FUtils::NormalizeToCircleAngle(RotateMeshAngle);

	//Checking for sufficient turn Mesh
	//if the mesh does not fall within the rotation gap, rotate it
	if (!(RotateMeshAngle > DirectionAngle - RotateDelta && RotateMeshAngle < DirectionAngle + RotateDelta))
	{
		//ClockwiseAngle - Angle Clockwise to Direction vector
		const float ClockwiseAngle = FUtils::NormalizeToCircleAngle(DirectionAngle - RotateMeshAngle);
		//ClockwiseAngle - Angle nticlockwise to Direction vector
		const float AnticlockwiseAngle = FUtils::NormalizeToCircleAngle(RotateMeshAngle - DirectionAngle);
		const float SignStepAngle = (ClockwiseAngle < AnticlockwiseAngle) ? 1 : -1;
		//AngleToDirection - the angle of the mildest turn up to Direction vector
		const float AngleToDirection = (ClockwiseAngle < AnticlockwiseAngle) ? ClockwiseAngle : AnticlockwiseAngle;
		//StepAngle - the angle how much the character will be rotated at the current step
		float StepAngle = StepAngleRotateMesh;
		if (AngleToDirection < StepAngle) StepAngle = AngleToDirection;
		const FRotator Rotator(0.0f, StepAngle * SignStepAngle, 0.0f);
		GetMesh()->AddLocalRotation(Rotator);
	}
}

void ARPGBaseCharacter::StartRun()
{
	Cast<URPGCharacterMovementComponent>(GetMovementComponent())->TurnOnWalkModifier();
}

void ARPGBaseCharacter::StopRun()
{
	Cast<URPGCharacterMovementComponent>(GetMovementComponent())->TurnOffWalkModifier();
}

void ARPGBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetCharacterMovement()->Velocity.Z;
	if (FallVelocityZ < LandedDamageVelocity.X) return;
	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(LogBaseCharacter, Display, TEXT("Player Take Damage Groud Landed:  %f"), FinalDamage);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void ARPGBaseCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	PlayAnimMontage(DeathAnimMontage);
	SetLifeSpan(5.0f);
	if (NeedSearchInteractive) GetWorld()->GetTimerManager().ClearTimer(SearchInteractiveTimer);
	if (NeedRotateMesh) GetWorld()->GetTimerManager().ClearTimer(RotateTimer);
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ARPGBaseCharacter::SearchInteractive()
{
	FoundInteractiveObject = nullptr;
	if (GetMovementComponent()->IsFalling()) return;
	FVector LineStart = CameraComponent->GetComponentLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	FVector LineEnd = LineStart + ForwardVector * DistanceSearch;

	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECollisionChannel::ECC_Visibility,
	                                     CollisionParams);
	if (HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 24, FColor::Red, false, -1, 0, 3.0f);
		auto InteractiveComponent = Cast<IInteractiveInterface>(HitResult.GetActor());
		if (!InteractiveComponent || !InteractiveComponent->IsCanInteractive(this)) return;
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 6.0f, 24, FColor::Green, false, -1, 0, 3.0f);
		FoundInteractiveObject = InteractiveComponent;
	}
}

void ARPGBaseCharacter::StartInteractive()
{
	if (FoundInteractiveObject) FoundInteractiveObject->InteractiveStart(this);
}
