
#include "SkateGameMode.h"
#include "UObject/ConstructorHelpers.h"

ASkateGameMode::ASkateGameMode()
{	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/C++/Player/BP_SkateCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
