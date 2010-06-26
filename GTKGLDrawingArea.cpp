#include "Globals.h"
#include "GTK++.h"

GTKGLDrawingArea::GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config, int PixFormat) :
	GTKDrawingArea(Width, Height), GTKGLWidget(Config, GTKDrawingArea::Widget, PixFormat)
{
}