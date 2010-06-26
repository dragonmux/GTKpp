#include "Globals.h"
#include "GTK++.h"

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

const GtkTextBuffer *GTKTextBuffer::GetBuffer()
{
	return TextBuffer;
}