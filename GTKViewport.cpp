#include "Globals.h"
#include "GTK++.h"

GTKViewport::GTKViewport(GTKWidget *Parent, int Width, int Height, BOOL NeedsParenting)
{
	HorAdj = new GTKAdjustment(Width, 1);
	VerAdj = new GTKAdjustment(Height, 1);
	Children.push_back(HorAdj);
	Children.push_back(VerAdj);
	Widget = gtk_viewport_new(HorAdj->GetAdjustment(), (GtkAdjustment *)VerAdj->GetAdjustment());
	Container = GTK_CONTAINER(Widget);
	Viewport = GTK_VIEWPORT(Container);
	if (NeedsParenting != FALSE)
		SetParent(Parent);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKViewport::SetParent(GTKWidget *Parent)
{
	((GTKContainer *)Parent)->AddChild(this);
}