/*
 * This file is part of GTK++ (libGTK++)
 * Copyright © 2012 Rachel Mant (dx-mon@users.sourceforge.net)
 *
 * GTK++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GTK++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdafx.h"

GTKCairoDrawingArea::GTKCairoDrawingArea(uint32_t width, uint32_t height) : GTKWidget(gtk_drawing_area_new()), Width(width), Height(height)
{
	DrawingArea = GTK_DRAWING_AREA(Widget);
	gtk_drawing_area_size(DrawingArea, Width, Height);
	SetHandler("expose-event", (void *)Redraw, this);
	Surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, Width, Height);
	Pixmap = cairo_create(Surface);
}

GTKCairoDrawingArea::~GTKCairoDrawingArea()
{
	cairo_destroy(Pixmap);
	cairo_surface_destroy(Surface);
}

void GTKCairoDrawingArea::DrawPoint(uint32_t X, uint32_t Y, const GTKCairoColour &Colour)
{
	DrawRect(X, Y, 1, 1, Colour);
}

void GTKCairoDrawingArea::DrawRect(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, const GTKCairoColour &Colour)
{
	cairo_set_source_rgb(Pixmap, Colour.R, Colour.G, Colour.B);
	cairo_rectangle(Pixmap, X, Y, Width, Height);
	cairo_fill(Pixmap);
}

void GTKCairoDrawingArea::DrawLine(uint32_t SrcX, uint32_t SrcY, uint32_t DstX, uint32_t DstY, const GTKCairoColour &Colour)
{
	cairo_set_source_rgb(Pixmap, Colour.R, Colour.G, Colour.B);
	cairo_move_to(Pixmap, SrcX, SrcY);
	cairo_line_to(Pixmap, DstX, DstY);
	cairo_fill(Pixmap);
}

void GTKCairoDrawingArea::FinishDrawing()
{
	gtk_widget_queue_draw(Widget);
}

bool GTKCairoDrawingArea::Redraw(GtkWidget *widget, GdkEventExpose *event, void *data)
{
	GTKCairoDrawingArea *DrawingArea = (GTKCairoDrawingArea *)data;
	cairo_t *gtkSurface = gdk_cairo_create(DrawingArea->Widget->window);

	cairo_set_source_surface(gtkSurface, DrawingArea->Surface, 0, 0);
	//cairo_rectangle(gtkSurface, 0, 0, DrawingArea->Width, DrawingArea->Height);
	//cairo_fill(gtkSurface);
	cairo_paint(gtkSurface);
	cairo_destroy(gtkSurface);
	return false;
}
