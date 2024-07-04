// Ullian Yunakh.


#include "TicTacToePlayerController.h"


void ATicTacToePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TArray<TEnumAsByte<EObjectTypeQuery>> objectsTypes;
	objectsTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic)); // columns is world static

	FHitResult hitResult;
	GetHitResultUnderCursorForObjects(objectsTypes, false, hitResult);
	
}
