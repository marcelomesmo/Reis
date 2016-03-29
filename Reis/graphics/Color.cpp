#include "Color.h"

Color* Color::Transparent = new Color(0, 0, 0, 0);
Color* Color::White = new Color(255, 255, 255);
Color* Color::Red = new Color(255, 0, 0);
Color* Color::Green = new Color(0, 255, 0);
Color* Color::Blue = new Color(0, 0, 255);
Color* Color::Black = new Color(0, 0, 0);

Color* Color::Cyan = new Color(0, 255, 255);
Color* Color::Orange = new Color(255, 165, 0);
Color* Color::Brown = new Color(184, 134, 11);
Color* Color::Yellow = new Color(255, 255, 0);
Color* Color::Purple = new Color(128, 0, 128);
Color* Color::Pink = new Color(255, 0, 255);

Color::Color(int red, int green, int blue, int alpha)
{
	/*
	 * Check first if values are valid: between 0 and 255.
	 * Set to 0 if invalid.
	 */
	if (red < 0 || red > 255) {
		printf("ERROR: Invalid Color Red value. Must be between 0 and 255.\n");
		red = (red < 0) ? 0 : 255;
	}
	if (green < 0 || green > 255) {
		printf("ERROR: Invalid Color Green value. Must be between 0 and 255.\n");
		green = (green < 0) ? 0 : 255;
	}
	if (blue < 0 || blue > 255) {
		printf("ERROR: Invalid Color Blue value. Must be between 0 and 255.\n");
		blue = (blue < 0) ? 0 : 255;
	}
	if (alpha < 0 || alpha > 255) {
		printf("ERROR: Invalid Color Alpha value. Must be between 0 and 255.\n");
		alpha = (alpha < 0) ? 0 : 255;
	}
	this->r = red;
	this->g = green;
	this->b = blue;
	this->a = alpha;
}