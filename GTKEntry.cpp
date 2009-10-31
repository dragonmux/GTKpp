#include "Globals.h"
#include "GTK++.h"

GTKEntry::GTKEntry(int Width, int Height, char *Content)
{
	Widget = gtk_entry_new();
	Entry = GTK_ENTRY(Widget);
	SetText(Content);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKEntry::SetText(char *Content)
{
	gtk_entry_set_text(Entry, Content);
}

int GTKEntry::GetTextLen()
{
	return gtk_entry_get_text_length(Entry);
}

void GTKEntry::GetText(char *Buff, int BuffLen)
{
	char *Text = (char *)gtk_entry_get_text(Entry);
	int Len = strlen(Text) + 1;
	memcpy(Buff, Text, (Len > BuffLen ? BuffLen : Len));
}