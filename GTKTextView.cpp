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
