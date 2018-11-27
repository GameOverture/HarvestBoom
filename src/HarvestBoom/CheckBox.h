#pragma once
#include "pch.h"

class CheckBox : public HyEntity2d
{
	bool			m_bIsChecked;

	HyPrimitive2d	m_Check;
	HyPrimitive2d	m_Box;
	HyPrimitive2d	m_BoxHighlight;

public:
	CheckBox(bool bIsForFood, HyEntity2d *pParent);

	void Sync();

	bool IsChecked();

protected:
	virtual void OnMouseEnter(void *pUserParam) override;
	virtual void OnMouseLeave(void *pUserParam) override;
	virtual void OnMouseDown(void *pUserParam) override;
	virtual void OnMouseUp(void *pUserParam) override;
	virtual void OnMouseClicked(void *pUserParam) override;
};
