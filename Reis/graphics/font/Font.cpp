#include "Font.h"

Font::Font(std::string filepath, int size, RenderType type, FontStyle style)
{
	//Initialize
	this->filepath = filepath;
	this->size = size;
	this->renderType = type;
	
	this->font = TTF_OpenFont(filepath.c_str(), size);
	if (!font)
	{
		printf("ERROR: Couldn't load font: %s.\n", filepath);
	}

	changeFontStyle(style);
}

Font::~Font()
{
	free();
}

void Font::free()
{
	//Free global font
	if (font != NULL)
	{
		TTF_CloseFont(this->font);
		font = NULL;
	}
	//printf("Closing font %s\n", filepath);
}

void Font::changeRenderType(RenderType renderType)
{
	this->renderType = renderType;
}

// Swap FontStyle from current one to new one.
void Font::changeFontStyle(FontStyle style)
{
	// ENUM STYLE
	this->fontStyle = style;

	// Getting SDL FONT style
	this->cur_style = TTF_STYLE_NORMAL;

	switch (style)
	{
		case FontStyle::BOLD:				cur_style = TTF_STYLE_BOLD;      break;
		case FontStyle::ITALIC:				cur_style = TTF_STYLE_ITALIC;    break;
		case FontStyle::UNDERLINE:			cur_style = TTF_STYLE_UNDERLINE; break;
		case FontStyle::STRIKETHROUGH:		cur_style = TTF_STYLE_STRIKETHROUGH; break;
		case FontStyle::NORMAL:	default:	break;
	}
	TTF_SetFontStyle(this->font, cur_style);
}

// Append a FontStyle to the current one.
void Font::addFontStyle(FontStyle style)
{
	// In case we try to add a normal font, resets to NORMAL
	if (style == FontStyle::NORMAL)
	{
		changeFontStyle(style);
	}
	else
	{
		// In case we try to add a new style, ENUM to MIXED
		this->fontStyle = FontStyle::MIXED;

		// Add new style by appending (bitwise OR) to old style (cur_style)
		switch (style)
		{
		case FontStyle::BOLD:				cur_style |= TTF_STYLE_BOLD;      break;
		case FontStyle::ITALIC:				cur_style |= TTF_STYLE_ITALIC;    break;
		case FontStyle::UNDERLINE:			cur_style |= TTF_STYLE_UNDERLINE; break;
		case FontStyle::STRIKETHROUGH:		cur_style |= TTF_STYLE_STRIKETHROUGH; break;
		case FontStyle::NORMAL:	default:	break;	// Never call this
		}
		TTF_SetFontStyle(this->font, cur_style);
	}
}

Font::RenderType Font::getRenderType() { return this->renderType; }
Font::FontStyle Font::getFontStyle() { return this->fontStyle; }

TTF_Font* Font::getFont() { return this->font; }