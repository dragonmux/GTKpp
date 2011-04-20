#include "Globals.h"
#include "GTK++.h"

GTKHBox::GTKHBox(BOOL EqualSpacing, int CellSpacing)
{
	Init(EqualSpacing, CellSpacing);
}

GTKHBox::GTKHBox(int Width, int Height, BOOL EqualSpacing, int CellSpacing)
{
	Init(EqualSpacing, CellSpacing);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKHBox::Init(BOOL EqualSpacing, int CellSpacing)
{
	Widget = gtk_hbox_new(EqualSpacing, CellSpacing);
	Container = GTK_CONTAINER(Widget);
	Box = GTK_BOX(Container);
	HBox = GTK_HBOX(Box);
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
