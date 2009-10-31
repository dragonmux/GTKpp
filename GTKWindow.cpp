#include "Globals.h"
#include "GTK++.h"

/***************************************************************\
|*                   GTKWindow implementation                  *|
\***************************************************************/

GTKWindow::GTKWindow(GtkWindowType Type, void *CloseFunc, void *data)
{
	Widget = gtk_window_new(Type);
	Window = GTK_WINDOW(Widget);
	gtk_window_set_gravity(Window, GDK_GRAVITY_NORTH_WEST);
	QuitProcID = SetHandler("delete_event", CloseFunc, data);
	QuitFunc = CloseFunc;
	QuitData = data;
	Events = NULL;
}

GTKWindow::~GTKWindow()
{
	DestroyGTKWidget();
	if (Events != NULL)
		delete Events;
	Window = NULL;
}

const GtkWindow *GTKWindow::GetWindow()
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

void GTKWindow::SetTitle(char *Title)
{
	gtk_window_set_title(Window, Title);
}

void GTKWindow::SetResizable(BOOL Resizable)
{
	gtk_window_set_resizable(Window, Resizable);
}

void GTKWindow::SetTool()
{
	SetResizable(FALSE);
	gtk_window_set_skip_taskbar_hint(Window, TRUE);
	gtk_window_set_type_hint(Window, GDK_WINDOW_TYPE_HINT_TOOLBAR);
}

void GTKWindow::SetParent(GTKWindow *Parent)
{
	gtk_widget_set_parent(Widget, (GtkWidget *)Parent->GetWidget());
}

void GTKWindow::SetModal(BOOL Mode, GTKWindow *Parent)
{
	if (Mode == TRUE && Parent == NULL)
		return;
	/*if (Mode == TRUE)
		gtk_window_set_transient_for(Window, (GtkWindow *)Parent->GetWindow());*/
	gtk_window_set_modal(Window, Mode);
}

RECT GTKWindow::GetWindowRect()
{
	int x, y;
	static RECT ret;
	gtk_window_get_position(Window, (int *)&ret.left, (int *)&ret.top);
	gtk_window_get_size(Window, &x, &y);
	ret.right = ret.left + x;
	ret.bottom = ret.top + y;
	return ret;
}

RECT GTKWindow::GetClientRect()
{
	int left, right, top, bottom;
	static RECT ret;
	GdkWindow *W = gdk_gl_window_get_window(gtk_widget_get_gl_window(Widget));
	gdk_window_get_position(W, &left, &top);
	gdk_window_get_size(W, &right, &bottom);
	ret.left = left;
	ret.top = top;
	ret.right = right + left;
	ret.bottom = bottom + top;
	return ret;
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

void GTKWindow::SetEventsHandled(int Events)
{
	gtk_widget_add_events(Widget, Events);
}

BOOL Redraw_Internal(void *W)
{
	GtkWidget *Widget = GTK_WIDGET(W);
	gdk_window_invalidate_rect(Widget->window, &Widget->allocation, TRUE);
	gdk_window_process_updates(Widget->window, TRUE);
	return TRUE;
}

void GTKWindow::Redraw()
{
	Redraw_Internal(Widget);
}

int GTKWindow::MessageBox(GtkMessageType Type, GtkButtonsType Buttons, char *Message, char *Title, ...)
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

char *GTKWindow::FileSave(char *Title, std::vector<char *> FileTypes, std::vector<char *> FileTypeNames)
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

char *GTKWindow::FileOpen(char *Title, std::vector<char *> FileTypes, std::vector<char *> FileTypeNames)
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
	gtk_widget_destroy(Widget);
}

void GTKWindow::SetEvents(GTKEvents *events)
{
	Events = events;
	events->Init(this);
}

const GTKEvents *GTKWindow::GetEvents()
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
	gtk_window_set_focus(Window, (GtkWidget *)Widget->GetWidget());
}

UINT GTKWindow::Subclass(void *SubQuitFunc, void *SubQuitData)
{
	UINT ret;
	RemoveHandler(QuitProcID);
	ret = SetHandler("delete_event", SubQuitFunc, SubQuitData);
	QuitProcID = SetHandler("delete_event", QuitFunc, QuitData);
	return ret;
}

void GTKWindow::Unsubclass(UINT SubQuitID)
{
	RemoveHandler(SubQuitID);
}