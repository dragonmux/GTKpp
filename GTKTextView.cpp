#include "stdafx.h"

GTKTextView::GTKTextView(GTKWidget *Parent, int Width, int Height, bool NeedsParenting) : GTKContainer(gtk_text_view_new()), AutoScroll(false)
{
	TextView = GTK_TEXT_VIEW(Container);
	if (NeedsParenting != FALSE)
		SetParent(Parent);
	gtk_widget_set_size_request(Widget, Width, Height);
	TextBuffer = new GTKTextBuffer();
	gtk_text_view_set_buffer(TextView, TextBuffer->GetBuffer());
}

GTKTextView::~GTKTextView()
{
	delete TextBuffer;
}

void GTKTextView::SetParent(GTKWidget *Parent)
{
	((GTKContainer *)Parent)->AddChild(this);
}

void GTKTextView::ClearText()
{
	TextBuffer->ClearText();
}

void GTKTextView::AddText(const char *Text)
{
	GtkTextMark *mark = TextBuffer->AddTextToEnd((char *)Text);
	if (AutoScroll == true)
		//gtk_text_view_scroll_mark_onscreen(TextView, mark);
	gtk_text_buffer_delete_mark(TextBuffer->GetBuffer(), mark);
	g_object_unref(G_OBJECT(mark));
}

void GTKTextView::SetAutoScrolling(bool Scrolling)
{
	AutoScroll = Scrolling;
}

void GTKTextView::SetEditable(bool Editable)
{
	gtk_text_view_set_editable(TextView, (Editable == false ? FALSE : TRUE));
}

void GTKTextView::SetWordWrapped(bool Wrapped)
{
	gtk_text_view_set_wrap_mode(TextView, (Wrapped == false ? GTK_WRAP_NONE : GTK_WRAP_WORD));
}
