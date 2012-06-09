#include "stdafx.h"

GTKLabel::GTKLabel(const char *Content) : GTKWidget(gtk_label_new(Content))
{
	Label = GTK_LABEL(Widget);
	gtk_label_set_ellipsize(Label, PANGO_ELLIPSIZE_END);
}

void GTKLabel::SetText(const char *Content)
{
	gtk_label_set_text(Label, Content);
	gtk_label_set_ellipsize(Label, PANGO_ELLIPSIZE_END);
}

void GTKLabel::SetSize(int Width, int Height)
{
	gtk_widget_set_size_request(Widget, Width, Height);
}

/**************\
|* Temporary: *|
\**************/
void GTKLabel::SetBackgroundColour(int R, int G, int B)
{
	PangoAttrList *Attrs = gtk_label_get_attributes(Label);
	PangoAttribute *Attr = pango_attr_background_new(R * 257, G * 257, B * 257);
	if (Attrs == NULL)
		Attrs = pango_attr_list_new();
	Attr->start_index = 0;
	Attr->end_index = 0xFFFFFFFF;
	pango_attr_list_change(Attrs, Attr);
	gtk_label_set_attributes(Label, Attrs);
}

void GTKLabel::SetUnderline(bool Underline)
{
	PangoAttrList *Attrs = gtk_label_get_attributes(Label);
	PangoAttribute *Attr = pango_attr_underline_new((Underline == FALSE ? PANGO_UNDERLINE_NONE : PANGO_UNDERLINE_SINGLE));
	if (Attrs == NULL)
		Attrs = pango_attr_list_new();
	Attr->start_index = 0;
	Attr->end_index = 0xFFFFFFFF;
	pango_attr_list_change(Attrs, Attr);
	gtk_label_set_attributes(Label, Attrs);
}

void GTKLabel::SetJustification(GTKJustification Placement)
{
	float Position = (Placement == GTKpp_JUSTIFY_LEFT ? 0 : (Placement == GTKpp_JUSTIFY_RIGHT ? 1 : 0.5F));
	gtk_misc_set_alignment(GTK_MISC(Widget), Position, 0.5F);
}
