#include "stdafx.h"

GTKHBox::GTKHBox(bool EqualSpacing, int CellSpacing) : GTKBox(gtk_hbox_new(EqualSpacing, CellSpacing))
{
	HBox = GTK_HBOX(Box);
}

GTKHBox::GTKHBox(int Width, int Height, bool EqualSpacing, int CellSpacing) : GTKBox(gtk_hbox_new(EqualSpacing, CellSpacing))
{
	HBox = GTK_HBOX(Box);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKHBox::SetParent(GTKWidget *Parent)
{
	gtk_container_add(GTK_CONTAINER(Parent->GetWidget()), Widget);
}

void GTKHBox::AddChild(GTKWidget *Child)
{
	gtk_box_pack_start_defaults(Box, Child->GetWidget());
	Children.push_back(Child);
}
