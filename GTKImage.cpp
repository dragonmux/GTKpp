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

GTKImage::GTKImage(int Width, int Height, bool UsingImage) : GTKWidget(gtk_event_box_new())
{
	this->UsingImage = UsingImage;
	if (UsingImage == FALSE)
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

void GTKImage::SetSize(int Width, int Height)
{
	if (UsingImage == FALSE)
		gtk_drawing_area_size(Image, Width, Height);
	else
		gtk_widget_set_size_request(_Widget, Width, Height);
	this->Width = Width;
	this->Height = Height;
}

void GTKImage::DrawImage(GDKPixbuf *Image)
{
	GdkColor Col = {0};
	GdkRectangle Rect;
	ASSERT_AND_RETURN("Cannot DrawImage on a gtk_image!\n", UsingImage == FALSE);
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
	ASSERT_AND_RETURN("Cannot SetImage on a gtk_drawing_area!\n", UsingImage != FALSE);
	gtk_image_set_from_pixbuf(this->Img, Image->GetBuffer());
}

void GTKImage::SetEventsHandled(int Events)
{
	gtk_widget_add_events(Widget, Events);
}
