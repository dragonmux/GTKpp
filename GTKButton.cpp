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

GTKButton::GTKButton(GtkWidget *Widget) : GTKWidget(Widget)
{
	Button = GTK_BUTTON(Widget);
}

GTKButton::GTKButton(const char *Content) : GTKWidget(gtk_button_new())
{
	Button = GTK_BUTTON(Widget);
	if (Content != NULL)
	{
		gtk_button_set_label(Button, Content);
		gtk_button_set_use_underline(Button, TRUE);
	}
}

void GTKButton::SetSize(int Width, int Height)
{
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKButton::SetImage(GtkWidget *Image)
{
	gtk_button_set_image(Button, Image);
}

void GTKButton::SetOnClicked(void *OnClickFunc, void *data)
{
	SetHandler("clicked", OnClickFunc, (data == NULL ? this : data));
}
