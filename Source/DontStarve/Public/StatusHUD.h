#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusHUD.generated.h"

class UImage;
class UPaperFlipbook;

UCLASS()
class DONTSTARVE_API UStatusHUD : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* Canvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Icon_Hunger;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Icon_Sanity;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Icon_Health;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* Icon_DayCicle;


	UPaperFlipbook* SpriteHealth;
	UPaperFlipbook* SpriteSanity;
	UPaperFlipbook* SpriteHunger;

	class ADSTCharacters* DSTChar;
public:
	void UpdateHealthWidget(float Damage);
	void UpdateSanityWidget(float Damage);
	void UpdateHungerWidget(float Damage);

};
