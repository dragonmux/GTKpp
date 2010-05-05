#include "Globals.h"
#include "GTK++.h"

GTKFrame::GTKFrame(GTKWidget *Parent, int Width, int Height, int X, int Y, char *Label) : GTKFixed(Width, Height)
{
	Frame = gtk_frame_new(Label);
	gtk_widget_set_size_request(Frame, Width, Height);
	SetParent(this);
	gtk_fixed_put(GTK_FIXED(Parent->GetWidget()), Frame, X, Y);
}

void GTKFrame::Enable()
{
	GTKWidget::Enable();
	gtk_widget_set_sensitive(Frame, TRUE);
}

void GTKFrame::Disable()
{
	GTKWidget::Disable();
	gtk_widget_set_sensitive(Frame, FALSE);
}