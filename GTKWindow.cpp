#include "Globals.h"
#include "GTK++.h"

/***************************************************************\
|*                   GTKWindow implementation                  *|
\***************************************************************/

GTKWindow::GTKWindow(GtkWindowType Type, void *CloseFunc, void *data)
{
	Widget = gtk_window_new(Type);
	Container = GTK_CONTAINER(Widget);
	Window = GTK_WINDOW(Container);
	gtk_window_set_gravity(Window, GDK_GRAVITY_NORTH_WEST);
	if (CloseFunc != NULL)
		SetHandler("delete_event", CloseFunc, data);
	else
		SetHandler("delete_event", (void *)gtk_main_quit, data);
	Events = NULL;
}

GTKWindow::~GTKWindow()
{
	DestroyGTKWidget();
	if (Events != NULL)
		delete Events;
	Window = NULL;
}

GtkWindow *GTKWindow::GetWindow() const
{
	return Window;
}

void GTKWindow::SetSize(int Width, int Height)
{
	gtk_window_resize(Window, Width, Height);
}

void GTKWindow::SetLocation(int X, int Y)
{
	gtk_window_move(Window, X, Y);
}

void GTKWindow::SetLocation(GtkWindowPosition Location)
{
	gtk_window_set_position(Window, Location);
}

void GTKWindow::SetTitle(const char *Title)
{
	gtk_window_set_title(Window, Title);
}

void GTKWindow::SetResizable(BOOL Resizable)
{
	gtk_window_set_resizable(Window, Resizable);
}

void GTKWindow::SetBorderless(BOOL Borderless)
{
	gtk_window_set_decorated(Window, (Borderless == FALSE ? TRUE : FALSE));
}

void GTKWindow::SetHideCloseButton(BOOL Hide)
{
	gtk_window_set_deletable(Window, (Hide == FALSE ? TRUE : FALSE));
}

void GTKWindow::SetTool()
{
	SetResizable(FALSE);
	gtk_window_set_skip_taskbar_hint(Window, TRUE);
	/******************************\
	|* What hint to use?!?!       *|
	|**--------------------------**|
	|* Well, this seems to work.. *|
	\******************************/
	gtk_window_set_type_hint(Window, GDK_WINDOW_TYPE_HINT_UTILITY);
}

void GTKWindow::SetParent(GTKWindow *Parent)
{
	gtk_widget_set_parent(Widget, Parent->GetWidget());
}

void GTKWindow::SetModal(BOOL Mode, GTKWindow *Parent)
{
	if (Mode == TRUE && Parent == NULL)
		return;
	if (Mode == TRUE)
		gtk_window_set_transient_for(Window, Parent->GetWindow());
	gtk_window_set_modal(Window, Mode);
}

void GTKWindow::SetMaximised(BOOL Maximised)
{
	if (Maximised == FALSE)
		gtk_window_unmaximize(Window);
	else
		gtk_window_maximize(Window);
}

RECT GTKWindow::GetWindowRect()
{
	static RECT ret;
	static GdkRectangle rc;
	gdk_window_get_frame_extents(Widget->window, &rc);
	ret.left = rc.x;
	ret.top = rc.y;
	ret.right = ret.left + rc.width;
	ret.bottom = ret.top + rc.height;
	return ret;
}

RECT GTKWindow::GetClientRect()
{
	//gdk_window_get_position // This could fix my possition problem as this is the actual location of the window which can be drawn on..
	int x, y, a, b;
	static RECT ret;
	gdk_window_get_position(Widget->window, (int *)&ret.left, (int *)&ret.top);
	gtk_window_get_position(Window, &a, &b);
	gtk_window_get_size(Window, &x, &y);
	ret.right = ret.left + x;
	ret.bottom = ret.top + y;
	return ret;
}

SIZE GTKWindow::GetDesktopSize()
{
	SIZE Desktop = {0};
	GdkWindow *wnd = gdk_window_get_toplevel(Widget->window);
	gdk_drawable_get_size(GDK_DRAWABLE(wnd), (int *)&Desktop.cx, (int *)&Desktop.cy);
	return Desktop;
}

void GTKWindow::ShowWindow()
{
	gtk_widget_show_all(Widget);
	gtk_window_get_focus(Window);
}

void GTKWindow::DoMessageLoop()
{
	BaseLoopLevel = gtk_main_level();
	gtk_main();
}

void GTKWindow::IterateMessageLoop()
{
	gtk_main_iteration();
}

void GTKWindow::SetEventsHandled(int Events)
{
	gtk_widget_add_events(Widget, Events);
}

void GTKWindow::Redraw(BOOL Now)
{
	gdk_window_invalidate_rect(Widget->window, NULL, TRUE);
	if (Now != FALSE)
		gdk_window_process_updates(Widget->window, TRUE);
}

int GTKWindow::MessageBox(GtkMessageType Type, GtkButtonsType Buttons, const char *Message, const char *Title, ...)
{
	va_list args;
	int ret;
	GTKMessageBox *Dialog;
	char *Tmp;
	va_start(args, Title);
	ret = vsnprintf(NULL, 0, Message, args) + 1;
	va_end(args);
	Tmp = (char *)malloc(ret);
	va_start(args, Title);
	vsprintf(Tmp, Message, args);
	va_end(args);
	Dialog = new GTKMessageBox(Window, Type, Buttons, Tmp, Title);
	free(Tmp);
	ret = Dialog->Run();
	delete Dialog;
	Dialog = NULL;
	return ret;
}

void GTKWindow::GetCursorPos(POINT *point, GdkModifierType *modifiers)
{
	gdk_window_get_pointer(Window->frame, (int *)&point->x, (int *)&point->y, modifiers);
}

char *GTKWindow::FileSave(const char *Title, std::vector<const char *> FileTypes, std::vector<const char *> FileTypeNames)
{
	int code;
	char *ret = NULL;
	GTKFileDialog *Dialog = new GTKFileDialog(Window, Title, GTK_FILE_CHOOSER_ACTION_SAVE, FileTypes, FileTypeNames,
		GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE_AS, GTK_RESPONSE_ACCEPT);
	code = Dialog->Run();

	if (code == GTK_RESPONSE_ACCEPT)
		ret = Dialog->GetSelectedFile();

	delete Dialog;
	return ret;
}

char *GTKWindow::FileOpen(const char *Title, std::vector<const char *> FileTypes, std::vector<const char *> FileTypeNames)
{
	int code;
	char *ret = NULL;
	GTKFileDialog *Dialog = new GTKFileDialog(Window, Title, GTK_FILE_CHOOSER_ACTION_OPEN, FileTypes, FileTypeNames,
		GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT);
	code = Dialog->Run();

	if (code == GTK_RESPONSE_ACCEPT)
		ret = Dialog->GetSelectedFile();

	delete Dialog;
	return ret;
}

void GTKWindow::ClientToScreen(RECT *Rect)
{
	RECT wndRect = GetClientRect();
	Rect->left += wndRect.left;
	Rect->top += wndRect.top;
	Rect->right += wndRect.left;
	Rect->bottom += wndRect.top;
	wndRect = GetWindowRect();
	Rect->left += wndRect.left;
	Rect->top += wndRect.top;
	Rect->right += wndRect.left;
	Rect->bottom += wndRect.top;
}

void GTKWindow::ScreenToClient(POINT *Point)
{
	ScreenToWindow(Point);
	WindowToClient(Point);
}

void GTKWindow::ScreenToWindow(POINT *Point)
{
	RECT wndRect;
	wndRect = GetWindowRect();
	Point->x -= wndRect.left;
	Point->y -= wndRect.top;
}

void GTKWindow::WindowToClient(POINT *Point)
{
	RECT cntRect;
	cntRect = GetClientRect();
	Point->x -= cntRect.left;
	Point->y -= cntRect.top;
}

void GTKWindow::Close()
{
	gtk_signal_emit_by_name(GTK_OBJECT(Widget), "delete_event");
}

void GTKWindow::Destroy()
{
	gtk_widget_destroy(Widget);
//	gtk_signal_emit_by_name(GTK_OBJECT(Widget), "destroy_event");
}

void GTKWindow::SetEvents(GTKEvents *events)
{
	Events = events;
	events->Init(this);
}

GTKEvents *GTKWindow::GetEvents() const
{
	return Events;
}

void GTKWindow::QuitAllMessageLoops()
{
	for (UINT i = gtk_main_level(); i > BaseLoopLevel; i--)
	{
		QuitMessageLoop();
	}
}

void GTKWindow::QuitMessageLoop()
{
	gtk_main_quit();
}

void GTKWindow::SetFocus(GTKWidget *Widget)
{
	gtk_window_set_focus(Window, Widget->GetWidget());
}
