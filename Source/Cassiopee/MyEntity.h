#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyEntity.generated.h"

UCLASS()
class CASSIOPEE_API AMyEntity : public ACharacter
{
	GENERATED_BODY()

public:
	AMyEntity();

	virtual void BeginPlay();
};
