#include "pch.h"
#include "InfoPanel.h"

InfoPanel::InfoPanel(const char *szPanelPrefix,
					 const char *szPanelName,
					 const char *szTextPrefix,
					 const char *szTextName,
					 int32 iTextOffsetX,
					 int32 iTextOffsetY,
					 int32 iTextDimensionsX,
					 int32 iTextDimensionsY,
					 HyEntity2d *pParent) :	HyEntity2d(pParent),
											m_pPanel(szPanelName != nullptr ? HY_NEW HySprite2d(szPanelPrefix, szPanelName, this) : nullptr),
											m_pText(szTextName != nullptr ? HY_NEW HyText2d(szTextPrefix, szTextName, this) : nullptr)
#ifdef DEV_QUICKMODE
											, m_pDebugTextBox(infoPanelInitRef.text_LoadPath.IsUsed() ? HY_NEW HyPrimitive2d(this) : nullptr)
#endif
{
	if(m_pText)
	{
		m_pText->TextSetAlignment(HYALIGN_Center);
		SetTextLocation(iTextOffsetX, iTextOffsetY, iTextDimensionsX, iTextDimensionsY);

#ifdef DEV_QUICKMODE
		m_pDebugTextBox->SetTint(1.0f, 0.0f, 0.0f);
#endif
	}

	UseWindowCoordinates();
}

InfoPanel::~InfoPanel()
{
	delete m_pPanel;
	delete m_pText;
#ifdef DEV_QUICKMODE
	delete m_pDebugTextBox;
#endif
}

HySprite2d *InfoPanel::GetPanelPtr()
{
	return m_pPanel;
}

HyText2d *InfoPanel::GetTextPtr()
{
	return m_pText;
}

/*virtual*/ void InfoPanel::SetPanelState(uint32 uiAnimIndex, bool bResetAnim)
{
	if(m_pPanel)
	{
		m_pPanel->AnimSetState(uiAnimIndex);

		if(bResetAnim)
			m_pPanel->AnimSetFrame(0);

		if(m_pText)
			SetTextLocation(m_vTextOffset.x, m_vTextOffset.y, static_cast<int32>(m_pText->TextGetBox().x), static_cast<int32>(m_pText->TextGetBox().y));
	}
}

float InfoPanel::GetPanelWidth()
{
	if(m_pPanel)
		return m_pPanel->AnimGetCurFrameWidth(true);
	
	return 0.0f;
}

float InfoPanel::GetPanelHeight()
{
	if(m_pPanel)
		return m_pPanel->AnimGetCurFrameHeight(true);

	return 0.0f;
}

/*virtual*/ std::string InfoPanel::GetStr()
{
	if(m_pText)
		return m_pText->TextGet();

	return std::string();
}

/*virtual*/ void InfoPanel::SetStr(std::string sText)
{
	if(m_pText)
		m_pText->TextSet(sText);
}

/*virtual*/ void InfoPanel::SetTextLocation(int32 iOffsetX, int32 iOffsetY, int32 iWidth, int32 iHeight)
{
	if(m_pText == nullptr)
		return;

	m_vTextOffset.x = iOffsetX;
	m_vTextOffset.y = iOffsetY;

	glm::ivec2 vPanelOffset(0);
	//if(m_pPanel)
	//{
	//	const HySprite2dData *pPanelData = static_cast<const HySprite2dData *>(m_pPanel->AcquireData());
	//	const HySprite2dFrame &frameRef = pPanelData->GetFrame(m_pPanel->AnimGetState(), m_pPanel->AnimGetFrame());
	//	vPanelOffset = frameRef.vOFFSET;
	//}
	
	m_pText->pos.Set(m_vTextOffset.x + vPanelOffset.x, m_vTextOffset.y + vPanelOffset.y);
	m_pText->SetAsScaleBox(static_cast<float>(iWidth), static_cast<float>(iHeight), true);

#ifdef DEV_QUICKMODE
	if(m_pDebugTextBox)
	{
		m_pDebugTextBox->pos.Set(m_pText->pos);
		m_pDebugTextBox->SetWireframe(true);
		m_pDebugTextBox->GetShape().SetAsBox(m_pText->TextGetBox().x, m_pText->TextGetBox().y);
	}
#endif
}

/*virtual*/ void InfoPanel::SetTextAlignment(HyAlign eAlignment)
{
	if(m_pText)
		m_pText->TextSetAlignment(eAlignment);
}

/*virtual*/ glm::vec2 InfoPanel::GetTextScaleBox()
{
	if(m_pText)
		return m_pText->TextGetBox();

	return glm::vec2(0.0f);
}
