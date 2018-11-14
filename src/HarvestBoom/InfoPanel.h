#pragma once
#include "pch.h"

class InfoPanel : public HyEntity2d
{
	friend class LgSlotGame;

protected:
	HySprite2d *			m_pPanel;
	HyText2d *				m_pText;

	glm::ivec2				m_vTextOffset;

#ifdef LG_DEBUG_BOXES
	HyPrimitive2d *			m_pDebugTextBox;
#endif

public:
	InfoPanel(const InfoPanelInit &infoPanelInitRef, HyEntity2d *pParent);
	virtual ~InfoPanel();

	HySprite2d *GetPanelPtr();
	HyText2d *GetTextPtr();

	virtual void SetPanelState(uint32 uiAnimIndex, bool bResetAnim = false);
	float GetPanelWidth();
	float GetPanelHeight();

	virtual std::string GetStr();
	virtual void SetStr(std::string sText);
	virtual void SetTextLocation(int32 iOffsetX, int32 iOffsetY, int32 iWidth, int32 iHeight);
	virtual void SetTextAlignment(HyAlign eAlignment);

	virtual glm::vec2 GetTextScaleBox();
};

