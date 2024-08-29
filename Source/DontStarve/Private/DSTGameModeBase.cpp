

#include "DSTGameModeBase.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "DSTPlayerController.h"
#include "DSTCharacters.h"

ADSTGameModeBase::ADSTGameModeBase()
{
	PlayerControllerClass = ADSTPlayerController::StaticClass();
	//DefaultPawnClass = AWilson::StaticClass();

	/*static ConstructorHelpers::FClassFinder<APawn>PlayerPawnBPClass(TEXT(""));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/

}

void ADSTGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
