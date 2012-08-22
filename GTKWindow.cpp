#include "stdafx.h"

#ifdef MessageBox
#undef MessageBox
#endif

#ifdef _MSC_VER
#define vsnprintf	_vsnprintf
#endif

/***************************************************************\
|*                   GTKWindow implementation                  *|
\***************************************************************/

GTKWindow::GTKWindow(GtkWindowType Type, void *CloseFunc, void *data) : GTKContainer(gtk_window_new(Type))
{
	Window = GTK_WINDOW(Container);
	gtk_window_set_gravity(Window, GDK_GRAVITY_NORTH_WEST);
	QuitFunc = (CloseFunc == NULL ? (void *)gtk_main_quit : CloseFunc);
	QuitData = data;
	RegisterQuitFunction();
	Events = NULL;
}

GTKWindow::~GTKWindow()
{
	delete Events;
	Window = NULL;
}

void GTKWindow::RegisterQuitFunction()
{
	QuitHandlerID = SetHandler("delete-event", QuitFunc, QuitData);
}

void GTKWindow::UnregisterQuitFunction()
{
	if (QuitHandlerID != 0)
		RemoveHandler(QuitHandlerID);
	QuitHandlerID = 0;
}

uint32_t GTKWindow::GetQuitHandlerID()
{
	return QuitHandlerID;
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

void GTKWindow::SetResizable(bool Resizable)
{
	gtk_window_set_resizable(Window, Resizable);
}

void GTKWindow::SetBorderless(bool Borderless)
{
	gtk_window_set_decorated(Window, (Borderless == false ? TRUE : FALSE));
}

void GTKWindow::SetHideCloseButton(bool Hide)
{
	gtk_window_set_deletable(Window, (Hide == false ? TRUE : FALSE));
}

void GTKWindow::SetTool(bool ShowInTaskbar)
{
	SetResizable(false);
	if (ShowInTaskbar == false)
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

void GTKWindow::SetModal(bool Mode, GTKWindow *Parent)
{
	if (Mode == TRUE && Parent == NULL)
		return;
	if (Mode == TRUE)
		gtk_window_set_transient_for(Window, Parent->GetWindow());
	gtk_window_set_modal(Window, Mode);
}

void GTKWindow::SetMaximised(bool Maximised)
{
	if (Maximised == FALSE)
		gtk_window_unmaximize(Window);
	else
		gtk_window_maximize(Window);
}

void GTKWindow::SetAlwaysOnTop()
{
	gtk_window_set_keep_above(Window, TRUE);
}

void GTKWindow::Present()
{
	gtk_window_present(Window);
}

GTKRect GTKWindow::GetWindowRect()
{
	static GTKRect ret;
	static GdkRectangle rc;
	gdk_window_get_frame_extents(Widget->window, &rc);
	ret.left = rc.x;
	ret.top = rc.y;
	ret.right = ret.left + rc.width;
	ret.bottom = ret.top + rc.height;
	return ret;
}

GTKRect GTKWindow::GetClientRect()
{
	//gdk_window_get_position // This could fix my possition problem as this is the actual location of the window which can be drawn on..
	int x, y, a, b;
	static GTKRect ret;
	gdk_window_get_position(Widget->window, (int *)&ret.left, (int *)&ret.top);
	gtk_window_get_position(Window, &a, &b);
	gtk_window_get_size(Window, &x, &y);
	ret.right = ret.left + x;
	ret.bottom = ret.top + y;
	return ret;
}

GTKSize GTKWindow::GetDesktopSize()
{
	GTKSize Desktop = {0};
	GdkWindow *wnd = gdk_get_default_root_window();
//	GdkScreen *screen = gtk_window_get_screen(Window);
//	Desktop.cx = gdk_screen_get_width(screen);
//	Desktop.cy = gdk_screen_get_height(screen);
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

void GTKWindow::GetCursorPos(GTKPoint *point, GdkModifierType *modifiers)
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

void GTKWindow::ClientToScreen(GTKRect *Rect)
{
	GTKRect wndRect = GetClientRect();
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

void GTKWindow::ScreenToClient(GTKPoint *Point)
{
	ScreenToWindow(Point);
	WindowToClient(Point);
}

void GTKWindow::ScreenToWindow(GTKPoint *Point)
{
	GTKRect wndRect;
	wndRect = GetWindowRect();
	Point->x -= wndRect.left;
	Point->y -= wndRect.top;
}

void GTKWindow::WindowToClient(GTKPoint *Point)
{
	GTKRect cntRect;
	cntRect = GetClientRect();
	Point->x -= cntRect.left;
	Point->y -= cntRect.top;
}

void GTKWindow::Close(GdkEvent *event)
{
	if (event != NULL)
		gdk_event_put(event);
	else
	{
		GdkEvent *delete_event = gdk_event_new(GDK_DELETE);
		delete_event->any.window = Widget->window;
		gdk_event_put(delete_event);
		gdk_event_free(delete_event);
	}
}

void GTKWindow::Destroy()
{
	gtk_widget_destroy(Widget);
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
	for (uint32_t i = gtk_main_level(); i > BaseLoopLevel; i--)
		QuitMessageLoop();
}

void GTKWindow::QuitMessageLoop()
{
	gtk_main_quit();
}

void GTKWindow::SetFocus(GTKWidget *Widget)
{
	gtk_window_set_focus(Window, Widget->GetWidget());
}

void GTKWindow::SetWindowIcon(GList *Icons)
{
	gtk_window_set_icon_list(Window, Icons);
}

void GTKWindow::SetFullscreen(bool Fullscreen)
{
	if (Fullscreen == true)
		gtk_window_fullscreen(Window);
	else
		gtk_window_unfullscreen(Window);
}
