#include "Globals.h"
#include "GTK++.h"

GTKLabel::GTKLabel(char *Content)
{
	Widget = gtk_label_new(Content);
	Label = GTK_LABEL(Widget);
}

void GTKLabel::SetText(char *Content)
{
	gtk_label_set_text(Label, Content);
}

void GTKLabel::SetSize(int Width, int Height)
{
	gtk_widget_set_size_request(Widget, Width, Height);
}