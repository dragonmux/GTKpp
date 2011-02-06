#include "Globals.h"
#include "GTK++.h"

GTKGLDrawingArea::GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config) :
	GTKDrawingArea(Width, Height), GTKGLWidget(Config, GTKDrawingArea::Widget)
{
}

GTKGLDrawingArea::GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config, int PixFormat) :
	GTKDrawingArea(Width, Height), GTKGLWidget(Config, GTKDrawingArea::Widget, PixFormat)
{
}

GTKGLDrawingArea::GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config, int PixFormat, bool AutoRedraw, int Timeout) :
	GTKDrawingArea(Width, Height), GTKGLWidget(Config, GTKDrawingArea::Widget, PixFormat, AutoRedraw, Timeout)
{
}