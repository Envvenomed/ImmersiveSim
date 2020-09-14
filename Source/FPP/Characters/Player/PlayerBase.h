// Copyright Veemo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBase.generated.h"

UENUM(Blueprintable)
enum class EMovementState : uint8
{
	EMovmentState_None UMETA(DisplayName = "None"),
	EMovmentState_Sprint UMETA(DisplayName = "Sprint"),
	EMovmentState_EdgeGrab UMETA(DisplayName = "EdgeGrab"),
	EMovmentState_Mantle UMETA(DisplayName = "Mantle"),
};

class UInputComponent;

UCLASS(config=Game)
class FPP_API APlayerBase : public ACharacter
{
	GENERATED_BODY()
	
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* MeshHands;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* SpellCastLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	APlayerBase();
	
protected:
	virtual void BeginPlay();

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	float MaxWalkSpeed = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	float MaxSprintSpeed = 2000.f;
	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category = CameraEffects)
	TSubclassOf<UCameraShake> SprintCameraShake;
	UPROPERTY(EditAnywhere, Category = CameraEffects)
	TSubclassOf<UCameraShake> RightWalkCameraShake;
	UPROPERTY(EditAnywhere, Category = CameraEffects)
	TSubclassOf<UCameraShake> LeftWalkCameraShake;
	
	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class AFPPProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;
	
protected:
	
	/** Fires a projectile. */
	void OnFire();

	void StartSprint();

	void EndSprint();

	void EdgeGrab();

	void Mantle();

	void Vault();
	
	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);
	
	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMeshHands() const { return MeshHands; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};


