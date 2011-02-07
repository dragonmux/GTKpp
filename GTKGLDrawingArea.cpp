#include "Globals.h"
#include "GTK++.h"

GTKGLDrawingArea::GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config) :
	GTKDrawingArea(Width, Height), GLBase(Config)
{
}

GTKGLDrawingArea::GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config, int PixFormat) :
	GTKDrawingArea(Width, Height), GLBase(Config)
{
}

GTKGLDrawingArea::GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config, int PixFormat, bool AutoRedraw, int Timeout) :
	GTKDrawingArea(Width, Height), GLBase(Config, PixFormat, AutoRedraw, Timeout)
{
}

GTKGLDrawingArea::~GTKGLDrawingArea()
{
}

GTKWidget *GTKGLDrawingArea::getGTKWidget()
{
	return GetGTKWidget();
}
