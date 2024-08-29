#include "DSTCharacters.h"
#include "StatusHud.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "PaperFlipbook.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraTypes.h"
#include "DSTPlayerController.h"
#include <Kismet/GameplayStatics.h>

ADSTCharacters::ADSTCharacters()
{
    PrimaryActorTick.bCanEverTick = false;

    PlayerHudClass = nullptr;
    PlayerHud = nullptr;

    ZoomLength = 2500.f;

    MaxHealth = 150.f;
    CurrentlHealth = MaxHealth;

    MaxSanity = 150.f;
    CurrentSanity = MaxSanity;

    MaxHunger = 150.f;
    CurrentHunger = MaxHunger;

    // CAPSULA DE COLISÃO
    GetCapsuleComponent()->InitCapsuleSize(80.f, 200.f);
    SetRootComponent(GetCapsuleComponent());

    // CAMERA BOOM
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    //CameraBoom->TargetArmLength = ZoomLength;
    CameraBoom->SetRelativeRotation(FRotator(342.f, 180.f, 0.f));

    // CRIA A CAMERA
    Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
    Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    Camera->SetOrthoWidth(ZoomLength);
    Camera->SetOrthoNearClipPlane(10.f);
    Camera->SetOrthoFarClipPlane(2097152.f);

    // MINHA SPRITE
    PaperMesh = GetSprite();


}

void ADSTCharacters::BeginPlay()
{
    Super::BeginPlay();



    if (IsLocallyControlled() && PlayerHudClass)
    {
        ADSTPlayerController* PLC = GetController<ADSTPlayerController>();
        check(PLC);
        PlayerHud = CreateWidget<UStatusHUD>(PLC, PlayerHudClass);
        check(PlayerHud);
        PlayerHud->AddToPlayerScreen();
    }
}

void ADSTCharacters::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADSTCharacters::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ADSTCharacters::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ADSTCharacters::MoveRight);
    PlayerInputComponent->BindAxis("Zoom", this, &ADSTCharacters::ZoomPlayer);

    PlayerInputComponent->BindAction("teste", IE_Pressed, this, &ADSTCharacters::TakeHealthDamage);
}

void ADSTCharacters::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

//Funções/Mecanicas
void ADSTCharacters::MoveForward(float Value)
{
    if (CurrentlHealth > 0.0f)
    {

    AddMovementInput(GetActorRightVector() * Value);
    if (Value != 0.f)
    {

        if (Value > 0.f)
        {
            MoveDirection = EMoveDirection::EMV_Up;
            SetAnimation(Up, 3.f);
        }
        else if (Value < 0.f)
        {
            MoveDirection = EMoveDirection::EMV_Down;
            SetAnimation(Down, 3.f);
        }

    }

    else // 1 = FALSE
    {
        if (IsMoveSideZero())
        {
            switch (MoveDirection)
            {
            case EMoveDirection::EMV_Up: { SetAnimation(IdleUp, 10.f); }
                                       break;

            case EMoveDirection::EMV_Down: { SetAnimation(IdleDown, 10.f); }
                                         break;

            default:
                break;
            }

        }
    }
   }
    else if (bIsDead)
    {
        AddMovementInput(GetActorRightVector() * Value);

    }
}

void ADSTCharacters::MoveRight(float Value)
{
    if (CurrentlHealth > 0.0f)
    {
         AddMovementInput(GetActorForwardVector() * Value);
          if (Value != 0.f)
            {
                if (IsMoveUpDownZero())// 0 = TRUE
                {
                    if (Value > 0.f)
                    {
                        MoveDirection = EMoveDirection::EMV_Right;
                        PaperMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
                        SetAnimation(Side, 3.f);
                    }
                    else if (Value < 0.f)
                    {
                        MoveDirection = EMoveDirection::EMV_Left;
                        PaperMesh->SetWorldScale3D(FVector(-1.0f, 1.0f, 1.0f));
                        SetAnimation(Side, 3.f);
                    }
                }
            }
             else // Value == 0.f
            {
                if (IsMoveUpDownZero())
                {
                    switch (MoveDirection)
                    {
                        case EMoveDirection::EMV_Right: { SetAnimation(IdleSide, 10.f); }
                                          break;

                        case EMoveDirection::EMV_Left: { SetAnimation(IdleSide, 10.f); }
                                         break;

                        default:
                                        break;
                    }
                }
            }
    }
    else if (bIsDead)
    {
        AddMovementInput(GetActorForwardVector() * Value);

    }
}

void ADSTCharacters::SetAnimation(UPaperFlipbook* Anim, float Rate)
{
    PaperMesh->SetFlipbook(Anim);
    PaperMesh->SetPlayRate(Rate);
}

void ADSTCharacters::TakeHealthDamage()
{
    PlayerHud->UpdateHealthWidget(50.f);
    if (CurrentlHealth == 0.f)
    {
        
        APlayerController* ctr = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (ctr)
        {
            ctr->DisableInput(ctr);
            SetAnimation(Death, 3.f);
            GetWorld()->GetTimerManager().SetTimer(Timer, this, &ADSTCharacters::IdleDeathAnimation, 2.f, false);
        }
    }
}

void ADSTCharacters::TakeSanityDamage(float Damage)
{
    PlayerHud->UpdateSanityWidget(Damage);
}

void ADSTCharacters::TakeHungerDamage(float Damage)
{
    PlayerHud->UpdateHungerWidget(Damage);
  
}

void ADSTCharacters::ZoomPlayer(float Value)
{
    if (Value > 0)
    {
        if (ZoomLength <= 2800.f)
        {
            ZoomLength += 20.f;
            Camera->SetOrthoWidth(ZoomLength);
        }
    }
    else if (Value < 0)
    {
        if (ZoomLength >= 1100.f)
        {
            ZoomLength -= 20.f;
            Camera->SetOrthoWidth(ZoomLength);
        }
    }
}

void ADSTCharacters::GhostAnimation()
{
    SetAnimation(Ghost, 3.f);
    GetWorld()->GetTimerManager().ClearTimer(Timer);
    APlayerController* ctr = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (ctr)
    {
        ctr->EnableInput(ctr);
        bIsDead = true;
    }
}

void ADSTCharacters::IdleDeathAnimation()
{
    SetAnimation(IdleDeath, 3.f);
    GetWorld()->GetTimerManager().ClearTimer(Timer);
    GetWorld()->GetTimerManager().SetTimer(Timer, this, &ADSTCharacters::GhostAnimation, 1.f, false);

}

bool ADSTCharacters::IsMoveUpDownZero()
{
    return FMath::IsNearlyZero(GetInputAxisValue("MoveForward"));
}

bool ADSTCharacters::IsMoveSideZero()
{
    return FMath::IsNearlyZero(GetInputAxisValue("MoveRight"));
}
