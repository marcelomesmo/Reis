#ifndef TTFFONT_H
#define TTFFONT_H

#include <SDL_ttf.h>
#include <string>

/**
 * @brief      TrueTypeFont (.ttf) implementation. 
 * 
 * @author     marcelomesmo
 */
class Font
{
public:
	/**
	 * Strongly typed enum for the Font's type of renderization. Low-level rendering options.
	 */
	enum class RenderType { SOLID, SHADED, BLENDED };
	/**
	 * Strongly typed enum for the Font's style. May have more than one type saved (MIXED).
	 */
	enum class FontStyle { NORMAL, BOLD, ITALIC, UNDERLINE, STRIKETHROUGH, MIXED };

	/**
	 * @brief      Initialize TTF Font.
	 *
	 * @param[in]  filepath  The location of the font to load.
	 * @param[in]  size      Font size.
	 * @param[in]  type      Font render type. SOLID by default.
	 * @param[in]  style     Font style. NORMAL by default.
	 */
	Font(std::string filepath, int size, RenderType type = RenderType::SOLID, FontStyle style = FontStyle::NORMAL);
	~Font();
	/**
	 * @brief      Clear the Font.
	 */
	void free();

	/**
	 * @brief      Sets the current font render type.
	 *
	 * @param[in]  type  Render type.
	 */
	void changeRenderType(RenderType type);
	/**
	 * @brief      Swap FontStyle from current one to new one.
	 *
	 * @param[in]  style  New font style.
	 */
	void changeFontStyle(FontStyle style);
	/**
	 * @brief      Append a FontStyle to the current one.
	 *
	 * @param[in]  style  New font style to append.
	 */
	void addFontStyle(FontStyle style);

	/**
	 * @brief      Return current render type.
	 *
	 * @return     A RenderType enum.
	 */
	RenderType getRenderType();
	/**
	 * @brief      Return current font style.
	 *
	 * @return     A FontStyle enum.
	 */
	FontStyle getFontStyle();

	/**
	 * @brief      Return TTF_Font file. Used to draw strings in Graphics.
	 *
	 * @return     A SDL TTF_Font.
	 */
	TTF_Font* getFont();

private:
	std::string  filepath;
	int          size;
	RenderType   renderType;
	FontStyle	 fontStyle;
	/**
	 * A list of all the current active styles for this font.
	 */
	int			 cur_style;

	/**
	 * The SDL Font to render.
	 */
	TTF_Font*    font;
};

#endif

