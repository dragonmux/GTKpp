#include "Globals.h"
#include "GTK++.h"

// extenal from GTKWindow API
extern BOOL Redraw_Internal(void *W);

#define TIMEOUT_INTERVAL 15

/***************************************************************\
|*                  GTKGLWindow implementation                 *|
\***************************************************************/

GTKGLWindow::GTKGLWindow(GtkWindowType Type, GdkGLConfig *Config, void *CloseFunc, int PixFormat, bool AutoRedraw) :
	GTKWindow(Type, CloseFunc), GTKGLWidget(Config, GTKWindow::Widget, PixFormat)
{
	TimeoutID = 0;
	if (AutoRedraw == true)
	{
		AddTimeout();
		GTKWindow::SetHandler("visibility_notify_event", (void *)CheckVisibility, this);
	}
}

BOOL GTKGLWindow::CheckVisibility(GtkWidget *widget, GdkEventVisibility *event, void *data)
{
	GTKGLWindow *Self = (GTKGLWindow *)data;
	if (event->state == GDK_VISIBILITY_FULLY_OBSCURED)
		Self->RemoveTimeout();
	else
		Self->AddTimeout();

	return TRUE;
}

void GTKGLWindow::AddTimeout()
{
	if (TimeoutID == 0)
#ifdef _WINDOWS
		TimeoutID = g_timeout_add(TIMEOUT_INTERVAL, Redraw_Internal, GTKWidget::Widget);
#else
		TimeoutID = g_timeout_add(TIMEOUT_INTERVAL, Redraw_Internal, GTKGLWidget::Widget);
#endif
}

void GTKGLWindow::RemoveTimeout()
{
	if (TimeoutID > 0)
	{
		g_source_remove(TimeoutID);
		TimeoutID = 0;
	}
}
