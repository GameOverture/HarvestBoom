#pragma once
#include "pch.h"

class BuyButton : public HyInfoPanel
{
public:
	BuyButton(HyEntity2d *pParent);

	bool IsUsed();

private:
	virtual void OnMouseDown() override;
	virtual void OnMouseUp() override;
	virtual void OnMouseLeave() override;
	virtual void OnMouseClicked() override;
};
