#include "Globals.h"
#include "GTK++.h"

GTKTextView::GTKTextView(GTKWidget *Parent, int Width, int Height, BOOL NeedsParenting) : AutoScroll(false)
{
	Widget = gtk_text_view_new();
	Container = GTK_CONTAINER(Widget);
	TextView = GTK_TEXT_VIEW(Container);
	if (NeedsParenting != FALSE)
		SetParent(Parent);
	gtk_widget_set_size_request(Widget, Width, Height);
	TextBuffer = new GTKTextBuffer();
	gtk_text_view_set_buffer(TextView, (GtkTextBuffer *)TextBuffer->GetBuffer());
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
	TextBuffer->AddTextToEnd((char *)Text);
	if (AutoScroll == true)
	{
		GtkTextIter Iter = {0};
		gtk_text_buffer_get_end_iter((GtkTextBuffer *)TextBuffer->GetBuffer(), &Iter);
		gtk_text_view_scroll_to_iter(TextView, &Iter, 0.0, FALSE, 0, 0);
	}
}

void GTKTextView::SetAutoScrolling(BOOL Scrolling)
{
	AutoScroll = (Scrolling == FALSE ? false : true);
}

void GTKTextView::SetEditable(BOOL Editable)
{
	gtk_text_view_set_editable(TextView, (Editable == FALSE ? FALSE : TRUE));
}

void GTKTextView::SetWordWrapped(BOOL Wrapped)
{
	gtk_text_view_set_wrap_mode(TextView, (Wrapped == FALSE ? GTK_WRAP_NONE : GTK_WRAP_WORD));
}
