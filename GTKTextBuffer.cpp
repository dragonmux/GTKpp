/*
 * This file is part of GTK++ (libGTK++)
 * Copyright © 2012 Richard/Rachel Mant (dx-mon@users.sourceforge.net)
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

GTKTextBuffer::GTKTextBuffer()
{
	TextBuffer = gtk_text_buffer_new(NULL);
}

GtkTextMark *GTKTextBuffer::AddTextToEnd(char *Text)
{
	GtkTextIter end;
	GtkTextMark *ret;
	gtk_text_buffer_get_end_iter(TextBuffer, &end);
	gtk_text_buffer_insert(TextBuffer, &end, Text, -1);
	ret = gtk_text_mark_new(NULL, FALSE);
	gtk_text_buffer_add_mark(TextBuffer, ret, &end);
	return ret;
}

void GTKTextBuffer::ClearText()
{
	GtkTextIter start, end;
	gtk_text_buffer_get_bounds(TextBuffer, &start, &end);
	gtk_text_buffer_delete(TextBuffer, &start, &end);
}

GtkTextBuffer *GTKTextBuffer::GetBuffer() const
{
	return TextBuffer;
}
