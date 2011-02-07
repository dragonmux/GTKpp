#include "Globals.h"
#include "GTK++.h"

GTKVBox::GTKVBox(int Width, int Height, BOOL EqualSpacing, int CellSpacing)
{
	Widget = gtk_vbox_new(EqualSpacing, CellSpacing);
	Container = GTK_CONTAINER(Widget);
	Box = GTK_BOX(Container);
	VBox = GTK_VBOX(Box);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKVBox::SetParent(GTKWidget *Parent)
{
	gtk_container_add(GTK_CONTAINER(Parent->GetWidget()), Widget);
}

void GTKVBox::AddWidget(GTKWidget *Child)
{
	gtk_box_pack_start_defaults(Box, Child->GetWidget());
	Children.push_back(Child);
}
