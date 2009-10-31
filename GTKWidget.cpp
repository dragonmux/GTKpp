#include "Globals.h"
#include "GTK++.h"

/***************************************************************\
|*                   GTKWidget implementation                  *|
\***************************************************************/

void GTKWidget::DestroyGTKWidget()
{
	gtk_widget_destroy(Widget);
}

const GtkWidget *GTKWidget::GetWidget()
{
	return Widget;
}

ULONG GTKWidget::SetHandler(char *Event, void *Handler, void *Data)
{
	return g_signal_connect(GTK_OBJECT(Widget), Event, G_CALLBACK(Handler), Data);
}

ULONG GTKWidget::SetHandlerAfter(char *Event, void *Handler, void *Data)
{
	return g_signal_connect_after(GTK_OBJECT(Widget), Event, G_CALLBACK(Handler), Data);
}

void GTKWidget::RemoveHandler(ULONG ID)
{
	g_signal_handler_disconnect(GTK_OBJECT(Widget), ID);
}

void GTKWidget::Disable()
{
	gtk_widget_set_sensitive(Widget, FALSE);
}

void GTKWidget::Enable()
{
	gtk_widget_set_sensitive(Widget, TRUE);
}