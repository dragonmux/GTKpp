#include "Globals.h"
#include "GTK++.h"

GDKPixbuf::GDKPixbuf(const char *File)
{
#ifdef _WINDOWS
	Buff = gdk_pixbuf_new_from_file_utf8(File, NULL);
#else
	Buff = gdk_pixbuf_new_from_file(File, NULL);
#endif
}

GDKPixbuf::GDKPixbuf(uint8_t *Data, uint32_t Width, uint32_t Height, uint32_t BPP, uint32_t CPP)
{
	Buff = gdk_pixbuf_new_from_data(Data, GDK_COLORSPACE_RGB, (CPP == 4 ? TRUE : FALSE), BPP / CPP, Width, Height, Width * CPP, NULL, NULL);
}

GDKPixbuf::GDKPixbuf(const uint8_t *InlineData)
{
	Buff = gdk_pixbuf_new_from_inline(-1, InlineData, FALSE, NULL);
}

GDKPixbuf::~GDKPixbuf()
{
	gdk_pixbuf_unref(Buff);
}

GdkPixbuf *GDKPixbuf::GetBuffer() const
{
	return Buff;
}
