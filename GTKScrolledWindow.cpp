#include "Globals.h"
#include "GTK++.h"

GTKScrolledWindow::GTKScrolledWindow(GTKWidget *Parent, int Width, int Height)
{
	Widget = gtk_scrolled_window_new(NULL, NULL);
	Container = GTK_CONTAINER(Widget);
	ScrolledWindow = GTK_SCROLLED_WINDOW(Container);
	SetParent(Parent);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKScrolledWindow::SetParent(GTKWidget *Parent)
{
	((GTKContainer *)Parent)->AddChild(this);
}

void GTKScrolledWindow::AddChild(GTKWidget *Child)
{
	gtk_container_add(Container, (GtkWidget *)Child->GetWidget());
}