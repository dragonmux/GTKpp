#include "Globals.h"
#include "GTK++.h"

GTKFixed::GTKFixed(GTKWidget *Parent, int Width, int Height)
{
	//GtkStyle *Style = gtk_style_new();
	Widget = gtk_fixed_new();
	Container = GTK_CONTAINER(Widget);
	Fixed = GTK_FIXED(Container);
	SetParent(Parent);
	/*gtk_style_set_font(Style, gdk_font_load("Courier New"));
	gtk_widget_set_style(Widget, Style);*/
	gtk_widget_set_size_request(Widget, Width, Height);
}

GTKFixed::GTKFixed(int Width, int Height)
{
	Widget = gtk_fixed_new();
	Container = GTK_CONTAINER(Widget);
	Fixed = GTK_FIXED(Container);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKFixed::SetParent(GTKWidget *Parent)
{
	((GTKContainer *)Parent)->AddChild(this);
}

void GTKFixed::SetLocation(GTKWidget *ChildWidget, int X, int Y)
{
	gtk_fixed_put(Fixed, (GtkWidget *)ChildWidget->GetWidget(), X, Y);
	Children.push_back(ChildWidget);
}

void GTKFixed::SetMove(GTKWidget *ChildWidget, int X, int Y)
{
	gtk_fixed_move(Fixed, (GtkWidget *)ChildWidget->GetWidget(), X, Y);
}