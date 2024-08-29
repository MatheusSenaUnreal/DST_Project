#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DONTSTARVE_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStatusComponent();

	friend class ADSTCharacters;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float MaxHealth;
private:
	//UPaperFlipbook* SpriteHealth;

		
};
