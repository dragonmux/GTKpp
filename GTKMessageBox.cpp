#include "Globals.h"
#include "GTK++.h"

/***************************************************************\
|*                 GTKMessageBox implementation                *|
\***************************************************************/

GTKMessageBox::GTKMessageBox(GtkWindow *Window, GtkMessageType Type, GtkButtonsType Buttons, char *Message, char *Title, ...) : GTKDialog()
{
	va_list args;
	char *Tmp = (char *)malloc(strlen(Message) + 255); // allocates 255 bytes extra space for vararg replacements.
	//TODO: Change this function (again!) to use vsnprintf() to work out how much space to allocate for Tmp.
	va_start(args, Title);
	//vsnprintf
	vsprintf(Tmp, Message, args);
	va_end(args);
	Widget = gtk_message_dialog_new(Window, GTK_DIALOG_MODAL, Type, Buttons, Tmp);
	free(Tmp);
	Dialog = GTK_DIALOG(Widget);
	gtk_window_set_title(GTK_WINDOW(Dialog), Title);
}

GTKMessageBox::~GTKMessageBox()
{
	DestroyGTKWidget();
}