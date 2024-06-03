#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ExistsUETestWidgetComponent.generated.h"

UCLASS()
class EXISTSUETEST_API UExistsUETestWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	void SetDisplayOnOwner(bool bInDiplayOnOwner);
	bool DisplaysOnOwner() const;
	
	virtual void InitWidget() override;

	template<typename T> requires(std::is_base_of_v<UUserWidget, T>)
	T* GetCastedWidget() const
	{
		return Cast<T>(GetWidget());
	}

protected:
	bool bDiplayOnOwner = false;

};
