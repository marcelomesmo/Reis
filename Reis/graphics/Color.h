#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

/**
 * @brief      A simple class represeting game Colors. Currently 11 (eleven)
 *             no-alpha colours and 1 (one) transparency defined here.
 *
 * @author     marcelomesmo
 * 
 */
class Color
{
public:
	Color(int red, int green, int blue, int alpha = 255);

	int r;
	int g;
	int b;
	int a;

	static Color* Transparent;
	static Color* White;
	static Color* Blue;
	static Color* Green;
	static Color* Red;
	static Color* Black;

	static Color* Cyan;
	static Color* Orange;
	static Color* Brown;
	static Color* Yellow;
	static Color* Purple;
	static Color* Pink;

};

#endif