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

/***************************************************************\
|*                    GTKImage implementation                  *|
\***************************************************************/

#define ASSERT_AND_RETURN(msg, exp) \
	{ \
		if (((exp)) == false) \
		{ \
			printf(msg); \
			return; \
		} \
	}

GTKImage::GTKImage(int Width, int Height, bool UsingImage) : GTKMisc(gtk_event_box_new(), false)
{
	this->UsingImage = UsingImage;
	if (UsingImage == false)
	{
		_Widget = gtk_drawing_area_new();
		Image = GTK_DRAWING_AREA(_Widget);
		DrawArea = NULL;
		GC = NULL;
	}
	else
	{
		_Widget = gtk_image_new();
		Img = GTK_IMAGE(_Widget);
	};
	EventBox = GTK_EVENT_BOX(Widget);
	gtk_event_box_set_visible_window(EventBox, FALSE);
	gtk_container_add(GTK_CONTAINER(Widget), _Widget);
	SetSize(Width, Height);
}

void GTKImage::SetSize(int width, int height)
{
	if (UsingImage == FALSE)
		gtk_drawing_area_size(Image, width, height);
	else
		gtk_widget_set_size_request(_Widget, width, height);
	Width = width;
	Height = height;
}

void GTKImage::DrawImage(GDKPixbuf *Image)
{
	GdkColor Col = {0};
	GdkRectangle Rect;
	ASSERT_AND_RETURN("Cannot DrawImage on a gtk_image!\n", UsingImage == false);
	if (DrawArea == NULL)
	{
		DrawArea = GDK_DRAWABLE(_Widget->window);
		GC = gdk_gc_new(DrawArea);
		gdk_gc_set_line_attributes(GC, 1, GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_BEVEL);
	}
	Rect.x = Rect.y = 0;
	Rect.width = Width;
	Rect.height = Height;
	gdk_window_begin_paint_rect(_Widget->window, &Rect);

	if (Image != NULL)
	{
		GdkPixbuf *Buff = Image->GetBuffer();
		int nWidth = gdk_pixbuf_get_width(Buff), nHeight = gdk_pixbuf_get_height(Buff);
		nWidth = (nWidth > Width ? Width : nWidth);
		nHeight = (nHeight > Height ? Height : nHeight);
		gdk_draw_pixbuf(DrawArea, GC, Buff, 0, 0, (Width - nWidth) / 2, (Height - nHeight) / 2, nWidth, nHeight, GDK_RGB_DITHER_NONE, 0, 0);
	}
	gdk_gc_set_rgb_fg_color(GC, &Col);
	gdk_draw_line(DrawArea, GC, 0, 0, Width - 1, 0);
	gdk_draw_line(DrawArea, GC, Width - 1, 0, Width - 1, Height - 1);
	gdk_draw_line(DrawArea, GC, Width - 1, Height - 1, 0, Height - 1);
	gdk_draw_line(DrawArea, GC, 0, Height - 1, 0, 0);
	gdk_window_end_paint(_Widget->window);
}

void GTKImage::SetImage(GDKPixbuf *Image)
{
	ASSERT_AND_RETURN("Cannot SetImage on a gtk_drawing_area!\n", UsingImage == true);
	gtk_image_set_from_pixbuf(this->Img, Image->GetBuffer());
}

void GTKImage::SetEventsHandled(int Events)
{
	gtk_widget_add_events(Widget, Events);
}
