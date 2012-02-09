#include "stdafx.h"

GTKVBox::GTKVBox(bool EqualSpacing, int CellSpacing)
{
	Init(EqualSpacing, CellSpacing);
}

GTKVBox::GTKVBox(int Width, int Height, bool EqualSpacing, int CellSpacing)
{
	Init(EqualSpacing, CellSpacing);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKVBox::Init(bool EqualSpacing, int CellSpacing)
{
	Widget = gtk_vbox_new(EqualSpacing, CellSpacing);
	Container = GTK_CONTAINER(Widget);
	Box = GTK_BOX(Container);
	VBox = GTK_VBOX(Box);
}

void GTKVBox::SetParent(GTKWidget *Parent)
{
	gtk_container_add(GTK_CONTAINER(Parent->GetWidget()), Widget);
}

void GTKVBox::AddChild(GTKWidget *Child)
{
	gtk_box_pack_start_defaults(Box, Child->GetWidget());
	Children.push_back(Child);
}
