#include "Globals.h"
#include "GTK++.h"

GTKTextBuffer::GTKTextBuffer()
{
	TextBuffer = gtk_text_buffer_new(NULL);
}

void GTKTextBuffer::AddTextToEnd(char *Text)
{
	GtkTextIter end;
	gtk_text_buffer_get_end_iter(TextBuffer, &end);
	gtk_text_buffer_insert(TextBuffer, &end, Text, -1);
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