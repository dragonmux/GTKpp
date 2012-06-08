#ifndef __GTKpp_H__
#define __GTKpp_H__

#include <vector>
#include <list>
#include <map>
#include <utility>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <pango/pango.h>

#include <inttypes.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#ifdef MessageBox
#ifdef UNICODE
#define __HAD_MessageBox__  MessageBoxW
#else
#define __HAD_MessageBox__  MessageBoxA
#endif /* UNICODE */
#undef MessageBox
#endif

#ifdef _WINDOWS
	#ifdef __GTKpp_EXPORT__
		#define GTKpp_API __declspec(dllexport)
	#else
		#define GTKpp_API __declspec(dllimport)
	#endif
#else
	#if __GNUC__ >= 4
		#define DEFAULT_VISIBILITY __attribute__ ((visibility("default")))
	#else
		#define DEFAULT_VISIBILITY
	#endif
	#define GTKpp_API DEFAULT_VISIBILITY
#endif

#ifndef GTK_GL_RGBA_TYPE
#define GDK_GL_RGBA_TYPE 0x8014
#endif

#define GTKpp_TIMEOUT_INTERVAL 15

typedef struct _GTKRect
{
	int32_t left;
	int32_t top;
	int32_t right;
	int32_t bottom;
} GTKRect;

typedef struct _GTKPoint
{
	int32_t x;
	int32_t y;
} GTKPoint;

typedef struct _GTKSize
{
	int32_t cx;
	int32_t cy;
} GTKSize;

typedef enum _GTKJustification
{
	GTKpp_JUSTIFY_LEFT,
	GTKpp_JUSTIFY_CENTER,
	GTKpp_JUSTIFY_RIGHT
} GTKJustification;

#ifndef __cdecl
#define __cdecl
#endif

class GTK
{
protected:
	GTK();
	~GTK();

public:
	GTKpp_API static void GTKInit(int _argc, char **_argv);
	GTKpp_API static void SetDefaultWindowIcon(GList *Icons);
};

#ifndef __NO_OPEN_GL__
class GTKGL : public GTK
{
private:
	GTKGL();
	~GTKGL();

public:
	GTKpp_API static void GTKInit(int _argc, char **_argv);
};

class GLBase;

class GTKFont
{
public:
	PangoFont *Font;
	uint32_t DisplayBase;
	int NumEntries, FontSize;
	GLBase *Parent;

	GTKpp_API GTKSize GetStringMetrics(const char *String);
};
#endif

class GTKWidget
{
protected:
	GtkWidget *Widget;

protected:
	GTKWidget();
	GTKWidget *GetGTKWidget() const;

public:
	GTKpp_API virtual ~GTKWidget();
	GTKpp_API GtkWidget *GetWidget() const;
	GTKpp_API uint32_t SetHandler(const char *Event, void *Handler, void *Data = NULL);
	GTKpp_API uint32_t SetHandlerAfter(const char *Event, void *Handler, void *Data = NULL);
	GTKpp_API void RemoveHandler(uint32_t ID);
	GTKpp_API void Disable();
	GTKpp_API void Enable();
	GTKpp_API void Hide();
	GTKpp_API void Show();
	GTKpp_API void Redraw(bool Now = false);
	GTKpp_API void SetForegroundColour(int R, int G, int B);
	GTKpp_API void SetBackgroundColour(int R, int G, int B);
	GTKpp_API void SetBold(bool Bold);
	GTKpp_API void SetItalic(bool Italic);
	GTKpp_API void SetUnderline(bool Underline);
	GTKpp_API void SetFontSize(int GTKSize);
	GTKpp_API void SetFontName(const char *Name);
};

#ifndef __NO_OPEN_GL__
class GLBase
{
private:
	GdkGLConfig *Conf;
	GdkGLContext *ctx;
	GdkGLDrawable *drw;
	std::vector<GTKFont *> Fonts;
	uint32_t TimeoutID, Timeout;
	static bool CheckVisibility(GtkWidget *widget, GdkEventVisibility *event, void *data);
	void init(GdkGLConfig *Config, int PixFormat);

protected:
	virtual GTKWidget *getGTKWidget() = 0;
	void GLBaseInit(GdkGLConfig *Config);
	void GLBaseInit(GdkGLConfig *Config, int PixFormat);
	void GLBaseInit(GdkGLConfig *Config, int PixFormat, bool AutoRedraw, int Timeout = GTKpp_TIMEOUT_INTERVAL);
	void GLBaseDeinit();

public:
	GTKpp_API bool glBegin();
	GTKpp_API void glSwapBuffers();
	GTKpp_API void glEnd();
	GTKpp_API GTKFont *SetupGLFont(const char *FontName, int GTKSize, int Start, int Num);
	GTKpp_API void DestroyGLFonts();
	GTKpp_API void DestroyGLFont(GTKFont **Font);
	GTKpp_API static GdkGLConfig *MakeStandardConfig();
	GTKpp_API void AddTimeout(int Timeout = GTKpp_TIMEOUT_INTERVAL);
	GTKpp_API void RemoveTimeout();
};
#endif

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
	GTKpp_API GTKMessageBox(GtkWindow *Window, GtkMessageType Type, GtkButtonsType Buttons, const char *Message, const char *Title, ...);
};

class GTKFileDialog : public GTKDialog
{
private:
	GtkFileChooser *FileDialog;
	GtkFileFilter *Filter;
	void AddFilters(std::vector<const char *> FileTypes, std::vector<const char *> FileTypeNames);
	void AddFilterChooser(std::vector<const char *> FileTypes, std::vector<const char *> FileTypeNames);

public:
	GTKpp_API GTKFileDialog(GtkWindow *Window, const char *Title, GtkFileChooserAction Action, std::vector<const char *> FileTypes,
		std::vector<const char *> FileTypeNames, const char *Button1_Type, int Button1_Result, const char *Button2_Type, int Button2_Result);
	GTKpp_API char *GetSelectedFile();
};

class GTKContainer : public GTKWidget
{
protected:
	GtkContainer *Container;
	std::list<GTKWidget *> Children;

public:
	GTKpp_API GTKContainer();
	GTKpp_API ~GTKContainer();
	GTKpp_API void AddChild(GTKWidget *Child);
	GTKpp_API void RemoveChild(GTKWidget *Child);
	GTKpp_API void SetBorder(int BorderWidth);
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
	void SetParent(GTKWidget *Parent);

public:
	GTKpp_API GTKFixed(GTKWidget *Parent, int Width, int Height);
	GTKpp_API void SetLocation(GTKWidget *ChildWidget, int X, int Y);
	GTKpp_API void SetMove(GTKWidget *ChildWidget, int X, int Y);
	GTKpp_API void SetSize(int Width, int Height);
};

class GTKHBox : public GTKBox
{
protected:
	GtkHBox *HBox;

private:
	void Init(bool EqualSpacing, int CellSpacing);

public:
	GTKpp_API GTKHBox(bool EqualSpacing = true, int CellSpacing = 0);
	GTKpp_API GTKHBox(int Width, int Height, bool EqualSpacing, int CellSpacing = 0);
	GTKpp_API void SetParent(GTKWidget *Parent);
	GTKpp_API void AddChild(GTKWidget *Child);
};

class GTKVBox : public GTKBox
{
protected:
	GtkVBox *VBox;

private:
	void Init(bool EqualSpacing, int CellSpacing);

public:
	GTKpp_API GTKVBox(bool EqualSpacing = true, int CellSpacing = 0);
	GTKpp_API GTKVBox(int Width, int Height, bool EqualSpacing, int CellSpacing = 0);
	GTKpp_API void SetParent(GTKWidget *Parent);
	GTKpp_API void AddChild(GTKWidget *Child);
};

class GTKLabel : public GTKWidget
{
protected:
	GtkLabel *Label;

public:
	GTKpp_API GTKLabel(const char *Content = NULL);
	GTKpp_API void SetText(const char *Content = NULL);
	GTKpp_API void SetSize(int Width, int Height);
	GTKpp_API void SetBackgroundColour(int R, int G, int B);
	GTKpp_API void SetUnderline(bool Underline);
	GTKpp_API void SetJustification(GTKJustification Placement);
};

class GTKButton : public GTKWidget
{
protected:
	GtkButton *Button;

public:
	GTKpp_API GTKButton(const char *Content = NULL);
	GTKpp_API void SetSize(int Width, int Height);
	GTKpp_API void SetImage(GtkWidget *Image);
	GTKpp_API void SetOnClicked(void *OnClickFunc, void *data = NULL);
};

class GDKPixbuf
{
protected:
	GdkPixbuf *Buff;

public:
	GTKpp_API GDKPixbuf(const char *File);
	GTKpp_API GDKPixbuf(uint8_t *Data, uint32_t Width, uint32_t Height, uint32_t BPP, uint32_t CPP);
	GTKpp_API GDKPixbuf(const uint8_t *InlineData);
	GTKpp_API ~GDKPixbuf();
	GTKpp_API GdkPixbuf *GetBuffer() const;
};

class GTKImage : public GTKWidget
{
protected:
	GtkWidget *_Widget;
	GtkDrawingArea *Image;
	GdkDrawable *DrawArea;
	GdkGC *GC;
	GtkImage *Img;
	GtkEventBox *EventBox;
	int Width, Height;
	bool UsingImage;

public:
	GTKpp_API GTKImage(int Width, int Height, bool UsingImage = false);
	GTKpp_API void SetSize(int Width, int Height);
	GTKpp_API void DrawImage(GDKPixbuf *Image);
	GTKpp_API void SetImage(GDKPixbuf *Image);
	GTKpp_API void SetEventsHandled(int Events);
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
	GTKpp_API GTKEntry(int Width, int Height, const char *Content = "");
	GTKpp_API void SetText(const char *Content = "");
	GTKpp_API int GetTextLen();
	GTKpp_API void GetText(char *Buff, int BuffLen);
};

class GTKKey
{
public:
	GTKpp_API static uint32_t GetDefaultModifiersMask();
	GTKpp_API static uint32_t ToUpper(uint32_t Key);
};

class GTKFrame : public GTKContainer
{
protected:
	GtkFrame *Frame;

private:
	void Init(const char *Label);

public:
	GTKpp_API GTKFrame(GTKWidget *Parent, int Width, int Height, const char *Label = NULL);
	GTKpp_API GTKFrame(const char *Label = NULL);
};

class GTKFixedFrame : public GTKFrame
{
protected:
	GTKFixed *Fixed;

public:
	GTKpp_API GTKFixedFrame(GTKWidget *Parent, int Width, int Height, const char *Label = NULL);
	GTKpp_API void SetLocation(GTKWidget *ChildWidget, int X, int Y);
	GTKpp_API void SetMove(GTKWidget *ChildWidget, int X, int Y);
	GTKpp_API void AddChild(GTKWidget *ChildWidget);
	GTKpp_API void Enable();
	GTKpp_API void Disable();
	GTKpp_API void Show();
	GTKpp_API void Hide();
};

class GTKEvents;// abstract;

class GTKWindow : public GTKContainer
{
private:
	GtkWindow *Window;
	GTKEvents *Events;
	void *QuitFunc;
	void *QuitData;
	uint32_t QuitHandlerID;

protected:
	uint32_t BaseLoopLevel;

public:
	GTKpp_API GTKWindow(GtkWindowType Type, void *CloseFunc = NULL, void *data = NULL);
	GTKpp_API ~GTKWindow();
	GTKpp_API GtkWindow *GetWindow() const;
	GTKpp_API void SetSize(int Width, int Height);
	GTKpp_API void SetLocation(int X, int Y);
	GTKpp_API void SetLocation(GtkWindowPosition Location);
	GTKpp_API void SetTitle(const char *Title);
	GTKpp_API void SetResizable(bool Resizable);
	GTKpp_API void SetModal(bool Mode, GTKWindow *Parent = NULL);
	GTKpp_API void SetTool(bool ShowInTaskbar = false);
	GTKpp_API void SetParent(GTKWindow *Parent);
	GTKpp_API void SetBorderless(bool Borderless = true);
	GTKpp_API void SetHideCloseButton(bool Hide = true);
	GTKpp_API void SetMaximised(bool Maximised = true);
	GTKpp_API GTKRect GetWindowRect();
	GTKpp_API GTKRect GetClientRect();
	GTKpp_API GTKSize GetDesktopSize();
	GTKpp_API void ShowWindow();
	GTKpp_API void DoMessageLoop();
	GTKpp_API void IterateMessageLoop();
	GTKpp_API void SetEventsHandled(int Events);
	GTKpp_API int MessageBox(GtkMessageType Type, GtkButtonsType Buttons, const char *Message, const char *Title, ...);
	GTKpp_API char *FileSave(const char *Title, std::vector<const char *> FileTypes, std::vector<const char *> FileTypeNames);
	GTKpp_API char *FileOpen(const char *Title, std::vector<const char *> FileTypes, std::vector<const char *> FileTypeNames);
	GTKpp_API void GetCursorPos(GTKPoint *GTKPoint, GdkModifierType *modifiers = NULL);
	GTKpp_API void ScreenToClient(GTKPoint *GTKPoint);
	GTKpp_API void ScreenToWindow(GTKPoint *GTKPoint);
	GTKpp_API void WindowToClient(GTKPoint *GTKPoint);
	GTKpp_API void ClientToScreen(GTKRect *GTKRect);
	GTKpp_API void Close(GdkEvent *Event = NULL);
	GTKpp_API void Destroy();
	GTKpp_API void SetEvents(GTKEvents *events);
	GTKpp_API GTKEvents *GetEvents() const;
	GTKpp_API void QuitMessageLoop();
	GTKpp_API void QuitAllMessageLoops();
	GTKpp_API void SetFocus(GTKWidget *Widget);
	GTKpp_API void RegisterQuitFunction();
	GTKpp_API void UnregisterQuitFunction();
	GTKpp_API uint32_t GetQuitHandlerID();
	GTKpp_API void SetAlwaysOnTop();
	GTKpp_API void Present();
	GTKpp_API void SetWindowIcon(GList *Icons);
	GTKpp_API void SetFullscreen(bool Fullscreen = true);
};

class GTKEvents// abstract
{
protected:
	GTKWindow *Window;

public:
	typedef struct _Events
	{
		bool (__cdecl *ButtonDown)(GtkWidget *widget, GdkEventButton *event, void *data);
		bool (__cdecl *ButtonUp)(GtkWidget *widget, GdkEventButton *event, void *data);
		bool (__cdecl *Paint)(GtkWidget *widget, GdkEventExpose *event, void *data);
		bool (__cdecl *MoveSize)(GtkWidget *widget, GdkEventConfigure *event, void *data);
		bool (__cdecl *MouseMove)(GtkWidget *widget, GdkEventMotion *event, void *data);
		bool (__cdecl *KeyDown)(GtkWidget *widget, GdkEventKey *event, void *data);
		bool (__cdecl *Close)(GtkWidget *widget, GdkEvent *event, void *data);
	} Events;

	GTKpp_API GTKEvents();
	GTKpp_API virtual void Init(GTKWindow *Wnd) = 0;
	GTKpp_API virtual void Deinit() = 0;
	Events EventHandlers;
};

#ifndef __NO_OPEN_GL__
class GTKGLWindow : public GTKWindow, public GLBase
{
protected:
	virtual GTKWidget *getGTKWidget();

public:
	GTKpp_API GTKGLWindow(GtkWindowType Type, GdkGLConfig *Config, void *CloseFunc = NULL,
		int PixFormat = GDK_GL_RGBA_TYPE, bool AutoRedraw = false, int Timeout = GTKpp_TIMEOUT_INTERVAL);
	GTKpp_API ~GTKGLWindow();
	//GTKpp_AVI GTKGLWindow(GtkWindowType Type, GdkGLConfig *Config, void *CloseFunc = NULL,
	//	bool AutoRedraw = false);
};
#endif

class GTKScrolledWindow : public GTKContainer
{
protected:
	GtkScrolledWindow *ScrolledWindow;
	void SetParent(GTKWidget *Parent);

public:
	GTKpp_API GTKScrolledWindow(GTKWidget *Parent, int Width, int Height, bool NeedsParenting = true);
	GTKpp_API void AddChild(GTKWidget *Child);
};

class GTKTextBuffer
{
protected:
	GtkTextBuffer *TextBuffer;

public:
	GTKTextBuffer();
	GtkTextMark *AddTextToEnd(char *Text);
	void ClearText();
	GtkTextBuffer *GetBuffer() const;
};

class GTKTextView : public GTKContainer
{
protected:
	GtkTextView *TextView;
	GTKTextBuffer *TextBuffer;
	void SetParent(GTKWidget *Parent);
	bool AutoScroll;

public:
	GTKpp_API GTKTextView(GTKWidget *Parent, int Width, int Height, bool NeedsParenting = true);
	GTKpp_API ~GTKTextView();
	GTKpp_API void ClearText();
	GTKpp_API void AddText(const char *Text);
	GTKpp_API void SetEditable(bool Editable = true);
	GTKpp_API void SetWordWrapped(bool Wrapped = false);
	GTKpp_API void SetAutoScrolling(bool Scrolling);
};

class GTKList : public GTKContainer
{
protected:
	GtkTreeView *ListView;
	GtkListStore *ListStore;
	GtkCellRenderer *Renderer;
	GtkTreeViewColumn *Column;
	void SetParent(GTKWidget *Parent);

public:
	GTKpp_API GTKList(GTKWidget *Parent, int Width, int Height, bool NeedsParenting = true);
	GTKpp_API ~GTKList();
	GTKpp_API void AddItem(char *Value);
	GTKpp_API void DeleteItem(char *Value);
	GTKpp_API void Clear();
};

class GTKCheckBox : public GTKButton
{
protected:
	GtkCheckButton *CheckButton;

public:
	GTKpp_API GTKCheckBox(int Width, int Height, const char *Content = NULL);
	GTKpp_API bool GetChecked();
	GTKpp_API void SetChecked(bool Checked = true);
};

typedef void (__cdecl * freeFn)(void *);

class GTKComboBoxEntry
{
public:
	const char *Text;
	int ComboPos;
	freeFn FreeFn;
};

class GTKComboBox : public GTKContainer
{
protected:
	GtkComboBox *ComboBox;
	void SetParent(GTKWidget *Parent);
	int lastPos;
	std::map<int, GTKComboBoxEntry> Items;

public:
	GTKpp_API GTKComboBox(GTKWidget *Parent, int Width, int Height, bool NeedsParenting = true);
	GTKpp_API ~GTKComboBox();
	GTKpp_API void AddItem(const char *Text, int EnumValue, freeFn FreeFn = free);
	GTKpp_API void DeleteItem(const char *Text);
	GTKpp_API void SetSelected(const char *Text);
	GTKpp_API void SetSelected(unsigned int EnumValue);
	GTKpp_API int GetSelected();
	GTKpp_API const char *getTextFor(unsigned int Value);
	GTKpp_API int getPossitionOf(const char *Value);
	GTKpp_API int getEnumFor(unsigned int Value);
};

class GTKColourSelectionDialog : public GTKDialog
{
private:
	static void OkClicked(GtkWidget *widget, void *data);
	static void CancelClicked(GtkWidget *widget, void *data);

protected:
	GtkColorSelectionDialog *Selector;

public:
	GTKpp_API GTKColourSelectionDialog();
	GTKpp_API void SetColour(char R, char G, char B);
	GTKpp_API void GetColour(char *R, char *G, char *B);
};

class GTKAboutDialog : public GTKDialog
{
protected:
	GtkAboutDialog *AboutBox;

public:
	GTKpp_API GTKAboutDialog(GTKWindow *Parent);
	GTKpp_API void SetProgram(const char *Name);
	GTKpp_API void SetVersion(const char *VersionString);
	GTKpp_API void SetCopyright(const char *Copyright);
	GTKpp_API void SetComments(const char *Comments);
	GTKpp_API void SetLicense(const char *License);
	GTKpp_API void SetWebsiteURL(const char *URL);
	GTKpp_API void SetWebsiteText(const char *Website);
	GTKpp_API void SetAuthors(const char **Authors);
};

/*class GTKAdjustment
{
protected:
	GtkAdjustment *Adjustment;

public:
	GTKpp_API GTKAdjustment(int Dim, int Unit);
	GTKpp_API void Adjust(int newDim);
	GTKpp_API void SrollBy(int Amount);
	GTKpp_API GtkAdjustment *GetAdjustment() const;
};

class GTKViewport : public GTKContainer
{
protected:
	GtkViewport *Viewport;
	GTKAdjustment *HorAdj, *VerAdj;
	void SetParent(GTKWidget *Parent);

public:
	GTKpp_API GTKViewport(GTKWidget *Parent, int Width, int Height, bool NeedsParenting = true);
	GTKpp_API ~GTKViewport();
};*/

class GTKDrawingArea : public GTKWidget
{
protected:
	GtkDrawingArea *DrawingArea;

public:
	GTKpp_API GTKDrawingArea(int Width, int Height);
	GTKpp_API void SetSize(int Width, int Height);
};

#ifndef __NO_OPEN_GL__
class GTKGLDrawingArea : public GTKDrawingArea, public GLBase
{
protected:
	virtual GTKWidget *getGTKWidget();

public:
	GTKpp_API GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config);
	GTKpp_API GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config, int PixFormat);
	GTKpp_API GTKGLDrawingArea(int Width, int Height, GdkGLConfig *Config, int PixFormat, bool AutoRedraw,
		int Timeout = GTKpp_TIMEOUT_INTERVAL);
	GTKpp_API ~GTKGLDrawingArea();
};
#endif

class GTKMenuShell : public GTKContainer
{
protected:
	GtkMenuShell *MenuShell;

public:
	GTKpp_API void AddChild(GTKWidget *Child, bool Append = true);
};

class GTKMenuBar : public GTKMenuShell
{
protected:
	GtkMenuBar *MenuBar;

public:
	GTKpp_API GTKMenuBar(GTKWidget *Parent, bool NeedsParenting = true);
};

class GTKMenu : public GTKMenuShell
{
protected:
	GtkMenu *Menu;

public:
	GTKpp_API GTKMenu(GTKWidget *Parent, bool NeedsParenting = true);
};

class GTKMenuItem : public GTKContainer
{
protected:
	GtkMenuItem *MenuItem;

public:
	GTKpp_API GTKMenuItem(const char *Value = "");
	GTKpp_API void SetMenuText(const char *Value);
	GTKpp_API void SetChildMenu(GTKMenu *Menu);
	GTKpp_API void SetOnClicked(void *OnClickFunc, void *data = NULL);
};

class GTKProgressBar : public GTKWidget
{
protected:
	GtkProgressBar *ProgressBar;
	int Max, Progress;

public:
	GTKpp_API GTKProgressBar();
	GTKpp_API GTKProgressBar(int Max);
	GTKpp_API void Increment();
	GTKpp_API void Reset();
	GTKpp_API void Pulse();
	GTKpp_API void SetMax(int Max);
	GTKpp_API void SetProgress(int Progress);
};

typedef void (__cdecl *ChangedCallback)(void *, double);

class GTKRange : public GTKWidget
{
protected:
	GtkRange *Range;

	GTKRange();
	void SetHandlers();
	~GTKRange();

private:
	std::vector<std::pair<ChangedCallback, void *> > OnChangedCallbacks;
	double StartVal;

	void CallOnChangedCallbacks();
	static bool ButtonPress(GtkWidget *, GdkEventButton *event, void *data);
	static bool ButtonRelease(GtkWidget *, GdkEventButton *event, void *data);
	static bool KeyPress(GtkWidget *, GdkEventKey *, void *data);
	static bool KeyRelease(GtkWidget *, GdkEventKey *, void *data);
	static bool Scroll(GtkWidget *widget, GdkEventScroll *, void *data);

public:
	GTKpp_API double GetValue();
	GTKpp_API void SetValue(double Value);
	GTKpp_API void SetOnChanged(ChangedCallback OnChangedFunc, void *data = NULL);
	GTKpp_API void SetIncrement(double Step);
	GTKpp_API void SetIncrement(double Step, double Page);
};

class GTKScale : public GTKRange
{
protected:
	GtkScale *Scale;

	GTKScale();
	~GTKScale();

public:
	GTKpp_API void SetDecimalPrecision(uint32_t Places = 0);
	GTKpp_API void SetValueDrawn(bool Drawn = true);
	GTKpp_API void SetValuePosition(GtkPositionType Position);
	GTKpp_API void AddMark(double MarkValue, GtkPositionType MarkPosition, const char *MarkText = NULL);
	GTKpp_API void ClearAllMarks();
};

class GTKHScale : public GTKScale
{
protected:
	GtkHScale *HScale;

public:
	GTKpp_API GTKHScale(double min = 0, double max = 100, double step = 1);
};

class GTKVScale : public GTKScale
{
protected:
	GtkVScale *VScale;

public:
	GTKpp_API GTKVScale(double min = 0, double max = 100, double step = 1);
};

class GTKSeparator : public GTKWidget
{
protected:
	GtkSeparator *Separator;

	GTKSeparator();
	~GTKSeparator();
};

class GTKHSeparator : public GTKSeparator
{
protected:
	GtkHSeparator *HSeparator;

public:
	GTKpp_API GTKHSeparator();
	GTKpp_API ~GTKHSeparator();
};

class GTKVSeparator : public GTKSeparator
{
protected:
	GtkVSeparator *VSeparator;

public:
	GTKpp_API GTKVSeparator();
	GTKpp_API ~GTKVSeparator();
};

#ifdef __HAD_MessageBox__
#define MessageBox __HAD_MessageBox__
#undef __HAD_MessageBox__
#endif /*__HAD_MessageBox__*/
#endif /*__GTKpp_H__*/
