#pragma once
#include "pch.h"

class InfoPanel : public HyEntity2d
{
	friend class LgSlotGame;

protected:
	HySprite2d *			m_pPanel;
	HyText2d *				m_pText;

	glm::ivec2				m_vTextOffset;

public:
	InfoPanel(const char *szPanelPrefix, const char *szPanelName, const char *szTextPrefix, const char *szTextName, int32 iTextOffsetX, int32 iTextOffsetY, int32 iTextDimensionsX, int32 iTextDimensionsY, HyEntity2d *pParent);
	InfoPanel(const char *szPanelPrefix, const char *szPanelName, HyEntity2d *pParent);
	virtual ~InfoPanel();

	HySprite2d *GetPanelPtr();
	HyText2d *GetTextPtr();

	virtual void SetPanelState(uint32 uiAnimIndex, bool bResetAnim = false);
	float GetPanelWidth();
	float GetPanelHeight();

	virtual std::string GetStr();
	virtual void SetStr(std::string sText);
	virtual void SetTextLocation(int32 iOffsetX, int32 iOffsetY, int32 iWidth, int32 iHeight);
	virtual void SetTextAlignment(HyTextAlign eAlignment);

	virtual glm::vec2 GetTextScaleBox();
};
