#include "Fonts.h"

//micross

void CFonts::Reload(float flDPI)
{
	m_mFonts[FONT_ESP] = { "micross", int(14.f * flDPI), FONTFLAG_OUTLINE, 0 };
	m_mFonts[FONT_ESP_FLAG] = { "Small Fonts", int(9.f * flDPI), FONTFLAG_DROPSHADOW, 0 };
	m_mFonts[FONT_ESP_HP] = { "Small Fonts", int(10.f * flDPI), FONTFLAG_DROPSHADOW, 0 };
	m_mFonts[FONT_INDICATORS] = { "micross", int(14.f * flDPI), FONTFLAG_OUTLINE, 0 };

	for (auto& [_, fFont] : m_mFonts)
	{
		if (fFont.m_dwFont = I::MatSystemSurface->CreateFont())
			I::MatSystemSurface->SetFontGlyphSet(fFont.m_dwFont, fFont.m_szName, fFont.m_nTall, fFont.m_nWeight, 0, 0, fFont.m_nFlags);
	}
}

const Font_t& CFonts::GetFont(EFonts eFont)
{
	return m_mFonts[eFont];
}