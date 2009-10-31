#include "Globals.h"
#include "GTK++.h"

GDKPixbuf::GDKPixbuf(char *File)
{
	Buff = gdk_pixbuf_new_from_file_utf8(File, NULL);
}

GDKPixbuf::GDKPixbuf(char *Data, int Width, int Height, int BPP, int CPP)
{
	Buff = gdk_pixbuf_new_from_data((BYTE *)Data, GDK_COLORSPACE_RGB, (CPP == 4 ? TRUE : FALSE), BPP / CPP, Width, Height, Width * CPP, NULL, NULL);
}

GDKPixbuf::~GDKPixbuf()
{
	gdk_pixbuf_unref(Buff);
}

const GdkPixbuf *GDKPixbuf::GetBuffer()
{
	return Buff;
}