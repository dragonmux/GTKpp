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
	g_object_unref(Buff);
}

GdkPixbuf *GDKPixbuf::GetBuffer() const
{
	return Buff;
}
