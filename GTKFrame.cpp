#include "stdafx.h"

GTKFrame::GTKFrame(GTKWidget *Parent, int Width, int Height, const char *Label) : GTKContainer(gtk_frame_new(Label))
{
	Frame = GTK_FRAME(Container);
	gtk_widget_set_size_request(Widget, Width, Height);
	((GTKContainer *) Parent)->AddChild(this);
}

GTKFrame::GTKFrame(const char *Label) : GTKContainer(gtk_frame_new(Label))
{
	Frame = GTK_FRAME(Container);
}
