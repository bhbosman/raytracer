#ifndef COLOR_H
#define COLOR_H


#include "Vector.h"
typedef Vector TColor;
#define COLOUR_RED		TColor(1.f, 0.f, 0.f)
#define COLOUR_GREEN	TColor(0.f, 1.f, 0.f)
#define COLOUR_BLUE		TColor(0.f, 0.f, 1.f)
#define COLOUR_WHITE	TColor(1.f, 1.f, 1.f)
#define COLOUR_YELLOW 	TColor(1.f, 1.f, 0.f)
#define COLOUR_BLACK 	TColor(.0f, .0f, .0f)
#define COLOUR_GREY 	TColor(.5f, .5f, .5f)


typedef unsigned int Pixel;


#endif // COLOR_H
