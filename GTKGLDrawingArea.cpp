#include "Globals.h"
#include "GTK++.h"

GTKGLDrawingArea::GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config) : GTKDrawingArea(Width, Height)
{
	GLBaseInit(Config);
}

GTKGLDrawingArea::GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config, int PixFormat) :
	GTKDrawingArea(Width, Height)
{
	GLBaseInit(Config);
}

GTKGLDrawingArea::GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config, int PixFormat, bool AutoRedraw, int Timeout) :
	GTKDrawingArea(Width, Height)
{
	GLBaseInit(Config, PixFormat, AutoRedraw, Timeout);
}

GTKGLDrawingArea::~GTKGLDrawingArea()
{
	GLBaseDeinit();
}

GTKWidget *GTKGLDrawingArea::getGTKWidget()
{
	return GetGTKWidget();
}
