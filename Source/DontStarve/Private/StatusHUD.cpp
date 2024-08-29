#include "StatusHUD.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "DSTCharacters.h"
#include "DSTPlayerController.h"

void UStatusHUD::NativeConstruct()
{
		Super::NativeConstruct();	
		
		
		APlayerController* PlayerControl = GetOwningPlayer();// Pega o PlayerController do player 
		if (PlayerControl)
		{
			APawn* PlayerPawn = PlayerControl->GetPawn();// Pega quem controla o controle
			if (PlayerPawn)
			{
				DSTChar = Cast<ADSTCharacters>(PlayerPawn);// Converte o Pawn para o tipo desejado
			}
		}

		SpriteHealth = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Sprites/Status/Health/PFB_HealthBar.PFB_HealthBar'"));// Guarda a reference do Flipbook da vida

        SpriteSanity = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Sprites/Status/Sanity/PFB_Sanity.PFB_Sanity'"));// Guarda a reference do Flipbook da sanidade

        SpriteHunger = LoadObject<UPaperFlipbook>(nullptr, TEXT("PaperFlipbook'/Game/Sprites/Status/Hunger/PFB_Hunger.PFB_Hunger'"));

        if (Icon_Hunger)
        {
            UPaperSprite* FrameHunger = SpriteHunger->GetSpriteAtFrame(0);
            if (FrameHunger)
            {
                UTexture2D* HungerTexture = FrameHunger->GetBakedTexture();
                Icon_Hunger->SetBrushFromTexture(HungerTexture);
            }
        }

        if (Icon_Sanity)
        {
            UPaperSprite* FrameSanity = SpriteSanity->GetSpriteAtFrame(0);
            if (FrameSanity)
            {
                UTexture2D* SanityTexture = FrameSanity->GetBakedTexture();
                Icon_Sanity->SetBrushFromTexture(SanityTexture);
            }
        }

		if (Icon_Health)// Se a imagem que represennta a vida for valida
		{
			UPaperSprite* FrameHealth = SpriteHealth->GetSpriteAtFrame(0);//Pega o frame da sprite de vida e guarda
			if (FrameHealth)// Se esse frame for valido
			{
				UTexture2D* HealthTexture = FrameHealth->GetBakedTexture();// Trasnforma o frame em textura 2D
				Icon_Health->SetBrushFromTexture(HealthTexture);// Muda a imagem da vida por esse frame 
			}
		}
}

void UStatusHUD::UpdateHealthWidget(float Damage)
{
    if (!DSTChar || !SpriteHealth || !Icon_Health)
    {
        return;
    }

    // Reduzir a saúde atual do personagem pelo dano recebido
    DSTChar->CurrentlHealth -= Damage;

    // Garantir que a saúde atual não seja menor que zero
    DSTChar->CurrentlHealth = FMath::Clamp(DSTChar->CurrentlHealth, 0.0f, DSTChar->MaxHealth);

    float MaxHealth = DSTChar->MaxHealth;

    // Calcular a quantidade de saúde representada por cada sprite
    float HealthPerSprite = MaxHealth / 47.0f;

    // Calcular o índice do sprite com base na saúde atual do personagem
    // Aqui, queremos que o índice aumente à medida que a saúde diminui
    int32 FrameIndex = FMath::Clamp(47 - FMath::FloorToInt(DSTChar->CurrentlHealth / HealthPerSprite), 0, SpriteHealth->GetNumFrames() - 1);

    // Obter o sprite correspondente ao índice calculado
    UPaperSprite* NewSpriteUpdate = SpriteHealth->GetSpriteAtFrame(FrameIndex);
    if (NewSpriteUpdate)
    {
        UTexture2D* NewTexture = NewSpriteUpdate->GetBakedTexture();
        if (NewTexture)
        {
            // Atualizar a textura do ícone de saúde
            Icon_Health->SetBrushFromTexture(NewTexture);
          
        }
    }
}

void UStatusHUD::UpdateSanityWidget(float Damage)
{
    if (!DSTChar || !Icon_Sanity || !SpriteSanity)
    {
        return;
    }

    DSTChar->CurrentSanity -= Damage;

    DSTChar->CurrentSanity = FMath::Clamp(DSTChar->CurrentSanity, 0.f, DSTChar->MaxSanity);

    float MaxSanity = DSTChar->MaxSanity;

    float SanityPerSprite = MaxSanity / 47;

    int32 FrameIndex = FMath::Clamp(47 - FMath::FloorToInt(DSTChar->CurrentSanity / SanityPerSprite), 0, SpriteSanity->GetNumFrames() - 1);

    UPaperSprite* SanityFrame = SpriteSanity->GetSpriteAtFrame(FrameIndex);
    if (SanityFrame)
    {
        UTexture2D* NewTextureSanity = SanityFrame->GetBakedTexture();
        Icon_Sanity->SetBrushFromTexture(NewTextureSanity);
    }

}

void UStatusHUD::UpdateHungerWidget(float Damage)
{
    if (!DSTChar || !Icon_Hunger || !SpriteHunger)
    {
        return;
    }

    DSTChar->CurrentHunger -= Damage;

    DSTChar->CurrentHunger = FMath::Clamp(DSTChar->CurrentHunger, 0.f, DSTChar->MaxHunger);

    float MaxHunger = DSTChar->MaxHunger;

    float HungerPerSprite = MaxHunger / 22;

    int32 FrameIndex = FMath::Clamp(22 - FMath::FloorToInt(DSTChar->CurrentHunger / HungerPerSprite), 0, SpriteHunger->GetNumFrames() - 1);

    UPaperSprite* HungerFrame = SpriteHunger->GetSpriteAtFrame(FrameIndex);
    if (HungerFrame)
    {
        UTexture2D* NewTextureHunger = HungerFrame->GetBakedTexture();
        Icon_Hunger->SetBrushFromTexture(NewTextureHunger);
    }
}
