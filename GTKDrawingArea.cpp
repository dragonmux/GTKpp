#include "stdafx.h"

GTKDrawingArea::GTKDrawingArea(int Width, int Height)
{
	Widget = gtk_drawing_area_new();
	DrawingArea = GTK_DRAWING_AREA(Widget);
	gtk_drawing_area_size(DrawingArea, Width, Height);
}

void GTKDrawingArea::SetSize(int Width, int Height)
{
	gtk_drawing_area_size(DrawingArea, Width, Height);
}