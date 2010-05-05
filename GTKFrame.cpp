#include "Globals.h"
#include "GTK++.h"

GTKFrame::GTKFrame(GTKWidget *Parent, int Width, int Height, int X, int Y, const char *Label) : GTKFixed(Width, Height)
{
	GtkWidget *tmp;
	tmp = Widget;
	Frame = gtk_frame_new(Label);
	gtk_widget_set_size_request(Frame, Width, Height);
//	gtk_container_add(Container, (GtkWidget *)Child->GetWidget());
	Widget = Frame;
	((GTKFixed *)Parent)->SetLocation(this, X, Y);
	Widget = tmp;
	gtk_container_add(GTK_CONTAINER(Frame), Widget);
//	SetParent(this);
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

void GTKFrame::Show()
{
	GTKWidget::Show();
	gtk_widget_show(Frame);
}

void GTKFrame::Hide()
{
	GTKWidget::Hide();
	gtk_widget_hide(Frame);
}
