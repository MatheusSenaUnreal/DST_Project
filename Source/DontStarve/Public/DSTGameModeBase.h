#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DSTGameModeBase.generated.h"

UCLASS()
class DONTSTARVE_API ADSTGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	ADSTGameModeBase();

protected:
	virtual void BeginPlay() override;
};
