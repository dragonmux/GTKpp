#include "Globals.h"
#include "GTK++.h"

GTKImage::GTKImage(int Width, int Height)
{
	Widget = gtk_drawing_area_new();
	Image = GTK_DRAWING_AREA(Widget);
	SetSize(Width, Height);
	DrawArea = NULL;
	GC = NULL;
}

void GTKImage::SetSize(int Width, int Height)
{
	gtk_drawing_area_size(Image, Width, Height);
	this->Width = Width;
	this->Height = Height;
}

void GTKImage::DrawImage(GDKPixbuf *Image)
{
	GdkColor Col = {0};
	GdkRectangle Rect;
	if (DrawArea == NULL)
	{
		DrawArea = GDK_DRAWABLE(Widget->window);
		GC = gdk_gc_new(DrawArea);
		gdk_gc_set_line_attributes(GC, 1, GDK_LINE_SOLID, GDK_CAP_BUTT, GDK_JOIN_BEVEL);
	}
	Rect.x = Rect.y = 0;
	Rect.width = Width;
	Rect.height = Height;
	gdk_window_begin_paint_rect(Widget->window, &Rect);

	if (Image != NULL)
	{
		GdkPixbuf *Buff = (GdkPixbuf *)Image->GetBuffer();
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
	gdk_window_end_paint(Widget->window);
}