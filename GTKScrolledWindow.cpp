#include "stdafx.h"

GTKScrolledWindow::GTKScrolledWindow(GTKWidget *Parent, int Width, int Height, bool NeedsParenting) : GTKContainer(gtk_scrolled_window_new(NULL, NULL))
{
	ScrolledWindow = GTK_SCROLLED_WINDOW(Container);
	if (NeedsParenting == true)
		SetParent(Parent);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKScrolledWindow::SetParent(GTKWidget *Parent)
{
	((GTKContainer *)Parent)->AddChild(this);
}

void GTKScrolledWindow::AddChild(GTKWidget *Child)
{
	gtk_container_add(Container, Child->GetWidget());
}
