#pragma once
#include "pch.h"
#include "InfoPanel.h"

class ContinueButton : public InfoPanel
{
public:
	ContinueButton(HyEntity2d *pParent);

	bool IsUsed();

private:
	virtual void OnMouseDown() override;
	virtual void OnMouseUp() override;
	virtual void OnMouseLeave() override;
	virtual void OnMouseClicked() override;
};
