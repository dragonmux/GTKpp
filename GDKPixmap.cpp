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

GDKPixmap::GDKPixmap(GTKWidget *Widget, uint32_t Width, uint32_t Height) : PixmapWidth(Width), PixmapHeight(Height)
{
	GtkWidget *widget = Widget->GetWidget();
	Pixmap = gdk_pixmap_new(widget->window, Width, Height, 24);
}

GDKPixmap::~GDKPixmap()
{
	gdk_pixmap_unref(Pixmap);
}

GdkPixmap *GDKPixmap::GetPixmap() const
{
	return Pixmap;
}

uint32_t GDKPixmap::GetWidth() const
{
	return PixmapWidth;
}

uint32_t GDKPixmap::GetHeight() const
{
	return PixmapHeight;
}

void GDKPixmap::DrawPoint(uint32_t X, uint32_t Y, const GTKColour &Colour)
{
	double R, G, B;
	cairo_t *cairoPixmap = gdk_cairo_create(Pixmap);

	R = Colour.R / 255.0;
	G = Colour.G / 255.0;
	B = Colour.B / 255.0;

	cairo_set_source_rgb(cairoPixmap, R, G, B);
	cairo_rectangle(cairoPixmap, X, Y, X + 1, Y + 1);
	cairo_fill(cairoPixmap);
	cairo_destroy(cairoPixmap);
}

void GDKPixmap::DrawRect(uint32_t X, uint32_t Y, uint32_t Width, uint32_t Height, const GTKColour &Colour)
{
	double R, G, B;
	cairo_t *cairoPixmap = gdk_cairo_create(Pixmap);

	R = Colour.R / 255.0;
	G = Colour.G / 255.0;
	B = Colour.B / 255.0;

	cairo_set_source_rgb(cairoPixmap, R, G, B);
	cairo_rectangle(cairoPixmap, X, Y, X + Width, Y + Height);
	cairo_fill(cairoPixmap);
	cairo_destroy(cairoPixmap);
}
