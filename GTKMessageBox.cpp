#include "stdafx.h"

/***************************************************************\
|*                 GTKMessageBox implementation                *|
\***************************************************************/

GTKMessageBox::GTKMessageBox(GtkWindow *Window, GtkMessageType Type, GtkButtonsType Buttons, const char *Message, const char *Title, ...) : GTKDialog()
{
	va_list args;
	int len;
	char *Tmp;
	va_start(args, Title);
	len = vsnprintf(NULL, 0, Message, args);
	va_end(args);
	Tmp = (char *)malloc(len + 1);
	va_start(args, Title);
	vsprintf(Tmp, Message, args);
	va_end(args);
	Widget = gtk_message_dialog_new(Window, GTK_DIALOG_MODAL, Type, Buttons, Tmp);
	free(Tmp);
	Dialog = GTK_DIALOG(Widget);
	gtk_window_set_title(GTK_WINDOW(Dialog), Title);
}
