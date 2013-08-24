/*
 * This file is part of GTK++ (libGTK++)
 * Copyright © 2012 Rachel Mant (dx-mon@users.sourceforge.net)
 *
 * GTK++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GTK++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "stdafx.h"

#ifdef _MSC_VER
#define vsnprintf	_vsnprintf
#endif

/***************************************************************\
|*                 GTKMessageBox implementation                *|
\***************************************************************/

GTKMessageBox::GTKMessageBox(GtkWindow *Window, GtkMessageType Type, GtkButtonsType Buttons, const char *Message, const char *Title, ...) :
	GTKDialog(gtk_invisible_new())
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
	g_object_unref(Widget);
	Widget = gtk_message_dialog_new(Window, GTK_DIALOG_MODAL, Type, Buttons, Tmp);
	gtk_widget_ref(Widget);
	free(Tmp);
	Dialog = GTK_DIALOG(Widget);
	gtk_window_set_title(GTK_WINDOW(Dialog), Title);
}
