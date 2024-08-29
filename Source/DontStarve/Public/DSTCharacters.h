#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "DSTCharacters.generated.h"

class UPaperFlipbook;

UENUM()
enum class EMoveDirection : uint8
{
	EMV_Idle,
	EMV_Left,
	EMV_Right,
	EMV_Up,
	EMV_Down,
};

UCLASS()
class DONTSTARVE_API ADSTCharacters : public APaperCharacter
{
	GENERATED_BODY()

public:
	ADSTCharacters();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, Category = "Sprites")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	class USpringArmComponent* CameraBoom;

	class UPaperFlipbookComponent* PaperMesh;

	// Animações idle
	UPROPERTY(EditAnywhere, Category = "Sprites")
	UPaperFlipbook* IdleDown;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	UPaperFlipbook* IdleUp;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	UPaperFlipbook* IdleSide;

	// Animações de movimento
	UPROPERTY(EditAnywhere, Category = "Sprites")
	UPaperFlipbook* Side;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	UPaperFlipbook* Up;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	UPaperFlipbook* Down;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	UPaperFlipbook* Death;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	UPaperFlipbook* IdleDeath;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	UPaperFlipbook* Death2;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	UPaperFlipbook* IdleDeath2;



	float ZoomLength;
	float AnimationSpeed;

	EMoveDirection MoveDirection;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UStatusHUD> PlayerHudClass;

	class UStatusHUD* PlayerHud;

	FTimerHandle Timer;
	bool bIsDead = false;
public:
	
	UPROPERTY(EditAnywhere, Category = "StatusBar")
	float MaxHealth;
	float CurrentlHealth;

	UPROPERTY(EditAnywhere, Category = "StatusBar")
	float MaxSanity;
    float CurrentSanity;

	UPROPERTY(EditAnywhere, Category = "StatusBar")
	float MaxHunger;
	float CurrentHunger;

	UPROPERTY(EditAnywhere, Category = "Sprites")
	UPaperFlipbook* Ghost;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void SetAnimation(UPaperFlipbook* Anim, float Rate);
	void TakeHealthDamage();
	void TakeSanityDamage(float Damage);
	void TakeHungerDamage(float Damage);
	void ZoomPlayer(float Value);
	void GhostAnimation();
	void IdleDeathAnimation();

	bool IsMoveUpDownZero();
	bool IsMoveSideZero();

public:
};
