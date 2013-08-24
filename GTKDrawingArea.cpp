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

#ifdef GTK_WIDGET_STATE
#define gtk_widget_get_state	GTK_WIDGET_STATE
#endif

GTKDrawingArea::GTKDrawingArea(uint32_t width, uint32_t height) : GTKWidget(gtk_drawing_area_new()), Pixmap(NULL), Width(width), Height(height)
{
	DrawingArea = GTK_DRAWING_AREA(Widget);
	gtk_drawing_area_size(DrawingArea, Width, Height);
	SetHandler("expose-event", (void *)Redraw, this);
}

void GTKDrawingArea::SetSize(uint32_t width, uint32_t height)
{
	Width = width;
	Height = height;
	gtk_drawing_area_size(DrawingArea, Width, Height);
}

void GTKDrawingArea::SetPixmap(GDKPixmap *pixmap)
{
	Pixmap = pixmap;
}

bool GTKDrawingArea::Redraw(GtkWidget *widget, GdkEventExpose *event, void *data)
{
	GTKDrawingArea *DrawingArea = (GTKDrawingArea *)data;
	GDKPixmap *Pixmap = DrawingArea->Pixmap;

	if (Pixmap == NULL)
	{
		cairo_t *cairoPixmap = gdk_cairo_create(widget->window);
		cairo_set_source_rgb(cairoPixmap, 0, 0, 0);
		cairo_rectangle(cairoPixmap, 0, 0, widget->allocation.width, widget->allocation.height);
		cairo_fill(cairoPixmap);
		cairo_destroy(cairoPixmap);
	}
	else
	{
		/*cairo_matrix_t transferMatrix;
		cairo_pattern_t *transferPattern;
		cairo_surface_t *transferSurface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, Pixmap->GetWidth(), Pixmap->GetHeight());
		cairo_t *cairoPixmap = gdk_cairo_create(widget->window);
		cairo_t *transferPixmap = cairo_create(transferSurface);

		gdk_cairo_set_source_window(transferPixmap, Pixmap->GetPixmap(), 0, 0);
		cairo_rectangle(transferPixmap, 0, 0, Pixmap->GetWidth(), Pixmap->GetHeight());
		cairo_fill(transferPixmap);
		cairo_destroy(transferPixmap);

		transferPattern = cairo_pattern_create_for_surface(transferSurface);
		cairo_matrix_init_scale(&transferMatrix, float(Pixmap->GetWidth()) / float(DrawingArea->Width), float(Pixmap->GetHeight()) / float(DrawingArea->Height));
		cairo_pattern_set_matrix(transferPattern, &transferMatrix);
		cairo_set_source(cairoPixmap, transferPattern);

		cairo_rectangle(cairoPixmap, 0, 0, DrawingArea->Width, DrawingArea->Height);
		cairo_fill(cairoPixmap);
		cairo_pattern_destroy(transferPattern);

		cairo_surface_destroy(transferSurface);*/
		gdk_draw_drawable(widget->window, widget->style->fg_gc[gtk_widget_get_state(widget)], Pixmap->GetPixmap(), event->area.x, event->area.y,
			event->area.x, event->area.y, event->area.width, event->area.height);
	}
	return false;
}

void GTKDrawingArea::FinishDrawing()
{
	gtk_widget_queue_draw(Widget);
}

