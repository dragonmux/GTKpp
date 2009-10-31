#include <vector>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <pango/pango.h>

#ifdef MessageBox
#undef MessageBox
#endif

#ifdef _WINDOWS
	#ifdef __GTKpp_EXPORT__
		#define GTKpp_API __declspec(dllexport)
	#else
		#define GTKpp_API __declspec(dllimport)
	#endif
#else
	// To be filled in on a Linux computer
#endif

class GTK
{
public:
	GTKpp_API static void GTKInit(int argc = __argc, char **argv = __argv);
};

class GTKGL : GTK
{
public:
	GTKpp_API static void GTKInit(int argc = __argc, char **argv = __argv);
};

class GTKFont
{
public:
	PangoFont *Font;
	UINT DisplayBase;
	int NumEntries, FontSize;

	GTKpp_API SIZE GetStringMetrics(char *String);
};

class GTKWidget
{
protected:
	GtkWidget *Widget;
	void DestroyGTKWidget();

public:
	GTKpp_API const GtkWidget *GetWidget();
	GTKpp_API ULONG SetHandler(char *Event, void *Handler, void *Data = NULL);
	GTKpp_API ULONG SetHandlerAfter(char *Event, void *Handler, void *Data = NULL);
	GTKpp_API void RemoveHandler(ULONG ID);
	GTKpp_API void Disable();
	GTKpp_API void Enable();
};

class GTKGLWidget : GTKWidget
{
private:
	GdkGLConfig *Conf;
	GdkGLContext *ctx;
	GdkGLDrawable *drw;
	std::vector<GTKFont *> Fonts;

public:
	GTKpp_API GTKGLWidget(GdkGLConfig *Config, GtkWidget *W, int PixFormat = GDK_GL_RGBA_TYPE);
	GTKpp_API static GdkGLConfig *MakeStandardConfig();
	GTKpp_API BOOL glBegin();
	GTKpp_API void glSwapBuffers();
	GTKpp_API void glEnd();
	GTKpp_API GTKFont *SetupGLFont(char *FontName, int Size, int Start, int Num);
	GTKpp_API void DestroyGLFonts();
	GTKpp_API ULONG glSetHandler(char *Event, void *Handler, void *Data = NULL);
	GTKpp_API void glRemoveHandler(ULONG ID);
};

class GTKDialog : public GTKWidget
{
protected:
	GtkDialog *Dialog;

public:
	GTKpp_API int Run();
};

class GTKMessageBox : public GTKDialog
{
public:
	GTKpp_API GTKMessageBox(GtkWindow *Window, GtkMessageType Type, GtkButtonsType Buttons, char *Message, char *Title, ...);
	GTKpp_API ~GTKMessageBox();
};

class GTKFileDialog : public GTKDialog
{
private:
	GtkFileChooser *FileDialog;
	GtkFileFilter *Filter;
	void AddFilters(std::vector<char *> FileTypes, std::vector<char *> FileTypeNames);
	void AddFilterChooser(std::vector<char *> FileTypes, std::vector<char *> FileTypeNames);

public:
	GTKpp_API GTKFileDialog(GtkWindow *Window, char *Title, GtkFileChooserAction Action, std::vector<char *> FileTypes, std::vector<char *> FileTypeNames,
		char *Button1_Type, int Button1_Result, char *Button2_Type, int Button2_Result);
	GTKpp_API ~GTKFileDialog();
	GTKpp_API char *GetSelectedFile();
};

class GTKContainer : public GTKWidget
{
protected:
	GtkContainer *Container;
};

class GTKBox : public GTKContainer
{
protected:
	GtkBox *Box;
};

class GTKFixed : public GTKContainer
{
protected:
	GtkFixed *Fixed;
	GTKFixed(int Width, int Height);
	void SetParent(GtkWidget *Parent);

public:
	GTKpp_API GTKFixed(GTKWidget *Parent, int Width, int Height);
	GTKpp_API void SetLocation(GTKWidget *ChildWidget, int X, int Y);
	GTKpp_API void SetMove(GTKWidget *ChildWidget, int X, int Y);
};

class GTKHBox : public GTKBox
{
protected:
	GtkHBox *HBox;

public:
	GTKpp_API GTKHBox(int Width, int Height, BOOL EqualSpacing = TRUE, int CellSpacing = 0);
	GTKpp_API void SetParent(GTKWidget *Parent);
	GTKpp_API void AddChild(GTKWidget *Child);
};

class GTKLabel : public GTKWidget
{
protected:
	GtkLabel *Label;

public:
	GTKpp_API GTKLabel(char *Content = NULL);
	GTKpp_API void SetText(char *Content = NULL);
	GTKpp_API void SetSize(int Width, int Height);
};

class GTKButton : public GTKWidget
{
protected:
	GtkButton *Button;

public:
	GTKpp_API GTKButton(char *Content = NULL);
	GTKpp_API void SetSize(int Width, int Height);
	GTKpp_API void SetImage(GtkWidget *Image);
	GTKpp_API void SetOnClicked(void *OnClickFunc, void *data = NULL);
};

class GDKPixbuf
{
protected:
	GdkPixbuf *Buff;

public:
	GTKpp_API GDKPixbuf(char *File);
	GTKpp_API GDKPixbuf(char *Data, int Width, int Height, int BPP, int CPP);
	GTKpp_API ~GDKPixbuf();
	GTKpp_API const GdkPixbuf *GetBuffer();
};

class GTKImage : public GTKWidget
{
protected:
	GtkDrawingArea *Image;
	GdkDrawable *DrawArea;
	int Width, Height;
	GdkGC *GC;

public:
	GTKpp_API GTKImage(int Width, int Height);
	GTKpp_API void SetSize(int Width, int Height);
	GTKpp_API void DrawImage(GDKPixbuf *Image);
};

class GTKHUpDown : public GTKHBox
{
protected:
	GTKButton *Left, *Right;
	GtkBox *UpDown;
	int Min, Max, Current;

public:
	GTKpp_API GTKHUpDown(int Width, int Height, void *IncrementFunc, void *DecrementFunc, void *data);
	GTKpp_API void SetRange(int Min, int Max);
	GTKpp_API int GetPos();
	GTKpp_API void SetPos(int Pos);
};

class GTKEntry : public GTKWidget
{
protected:
	GtkEntry *Entry;

public:
	GTKpp_API GTKEntry(int Width, int Height, char *Content = "");
	GTKpp_API void SetText(char *Content = "");
	GTKpp_API int GetTextLen();
	GTKpp_API void GetText(char *Buff, int BuffLen);
};

class GTKKey
{
public:
	GTKpp_API static UINT GetDefaultModifiersMask();
	GTKpp_API static UINT ToUpper(UINT Key);
};

class GTKFrame : public GTKFixed
{
protected:
	GtkWidget *Frame;

public:
	GTKpp_API GTKFrame(GTKWidget *Parent, int Width, int Height, int X, int Y, char *Label = NULL);
	GTKpp_API void Enable();
	GTKpp_API void Disable();
};

class GTKEvents abstract;

class GTKWindow : public GTKWidget
{
private:
	GtkWindow *Window;
	GTKEvents *Events;

protected:
	UINT BaseLoopLevel;
	UINT QuitProcID;
	void *QuitFunc, *QuitData;

public:
	GTKpp_API GTKWindow(GtkWindowType Type, void *CloseFunc = gtk_main_quit, void *data = NULL);
	GTKpp_API ~GTKWindow();
	GTKpp_API const GtkWindow *GetWindow();
	GTKpp_API void SetSize(int Width, int Height);
	GTKpp_API void SetLocation(int X, int Y);
	GTKpp_API void SetLocation(GtkWindowPosition Location);
	GTKpp_API void SetTitle(char *Title);
	GTKpp_API void SetResizable(BOOL Resizable);
	GTKpp_API void SetModal(BOOL Mode, GTKWindow *Parent = NULL);
	GTKpp_API void SetTool();
	GTKpp_API void SetParent(GTKWindow *Parent);
	GTKpp_API RECT GetWindowRect();
	GTKpp_API RECT GetClientRect();
	GTKpp_API void ShowWindow();
	GTKpp_API void DoMessageLoop();
	GTKpp_API void SetEventsHandled(int Events);
	GTKpp_API void Redraw();
	GTKpp_API int MessageBox(GtkMessageType Type, GtkButtonsType Buttons, char *Message, char *Title, ...);
	GTKpp_API char *FileSave(char *Title, std::vector<char *> FileTypes, std::vector<char *> FileTypeNames);
	GTKpp_API char *FileOpen(char *Title, std::vector<char *> FileTypes, std::vector<char *> FileTypeNames);
	GTKpp_API void GetCursorPos(POINT *point, GdkModifierType *modifiers = NULL);
	GTKpp_API void ScreenToClient(POINT *Point);
	GTKpp_API void ScreenToWindow(POINT *Point);
	GTKpp_API void WindowToClient(POINT *Point);
	GTKpp_API void Close();
	GTKpp_API void SetEvents(GTKEvents *events);
	GTKpp_API const GTKEvents *GetEvents();
	GTKpp_API void QuitMessageLoop();
	GTKpp_API void QuitAllMessageLoops();
	GTKpp_API void SetFocus(GTKWidget *Widget);
	GTKpp_API UINT Subclass(void *SubQuitFunc, void *SubQuitData);
	GTKpp_API void Unsubclass(UINT SubQuitID);
};

class GTKEvents abstract
{
protected:
	GTKWindow *Window;

public:
	typedef struct _Events
	{
		BOOL (__cdecl *ButtonDown)(GtkWidget *widget, GdkEventButton *event, void *data);
		BOOL (__cdecl *Paint)(GtkWidget *widget, GdkEventExpose *event, void *data);
		BOOL (__cdecl *MoveSize)(GtkWidget *widget, GdkEventConfigure *event, void *data);
		BOOL (__cdecl *MouseMove)(GtkWidget *widget, GdkEventMotion *event, void *data);
		BOOL (__cdecl *KeyDown)(GtkWidget *widget, GdkEventKey *event, void *data);
	} Events;

	GTKpp_API virtual void Init(GTKWindow *Wnd) = 0;
	GTKpp_API virtual void Deinit() = 0;
	Events EventHandlers;
};

class GTKGLWindow : public GTKWindow, public GTKGLWidget
{
private:
	static BOOL CheckVisibility(GtkWidget *widget, GdkEventVisibility *event, void *data);
	UINT TimeoutID;

public:
	GTKpp_API GTKGLWindow(GtkWindowType Type, GdkGLConfig *Config, void *CloseFunc = gtk_main_quit, int PixFormat = GDK_GL_RGBA_TYPE);
	GTKpp_API void AddTimeout();
	GTKpp_API void RemoveTimeout();
};