#include "stdafx.h"

GTKFrame::GTKFrame(GTKWidget *Parent, int Width, int Height, const char *Label) : GTKContainer()
{
	Init(Label);
	gtk_widget_set_size_request(Widget, Width, Height);
	((GTKContainer *) Parent)->AddChild(this);
}

GTKFrame::GTKFrame(const char *Label) : GTKContainer()
{
	Init(Label);
}

void GTKFrame::Init(const char *Label)
{
	Widget = gtk_frame_new(Label);
	Container = GTK_CONTAINER(Widget);
	Frame = GTK_FRAME(Container);
}
