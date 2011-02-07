#include "Globals.h"
#include "GTK++.h"

GTKHBox::GTKHBox(int Width, int Height, BOOL EqualSpacing, int CellSpacing)
{
	Widget = gtk_hbox_new(EqualSpacing, CellSpacing);
	Container = GTK_CONTAINER(Widget);
	Box = GTK_BOX(Container);
	HBox = GTK_HBOX(Box);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKHBox::SetParent(GTKWidget *Parent)
{
	gtk_container_add(GTK_CONTAINER(Parent->GetWidget()), Widget);
}

void GTKHBox::AddWidget(GTKWidget *Child)
{
	gtk_box_pack_start_defaults(Box, Child->GetWidget());
	Children.push_back(Child);
}
