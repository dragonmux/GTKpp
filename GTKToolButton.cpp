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

GTKToolButton::GTKToolButton(GTKMisc *icon, const char *Text) : GTKToolItem(gtk_tool_button_new(icon->GetWidget(), Text)), Icon(icon)
{
	ToolButton = GTK_TOOL_BUTTON(ToolItem);
}

GTKToolButton::GTKToolButton(GTKMisc *icon) : GTKToolItem(gtk_tool_button_new(icon->GetWidget(), NULL)), Icon(icon)
{
	ToolButton = GTK_TOOL_BUTTON(ToolItem);
}

GTKToolButton::GTKToolButton(const char *Text, bool Stock) : GTKToolItem(), Icon(NULL)
{
	g_object_unref(Widget);
	if (Stock)
		ToolItem = gtk_tool_button_new_from_stock(Text);
	else
		ToolItem = gtk_tool_button_new(NULL, Text);
	Widget = GTK_WIDGET(ToolItem);
	Container = GTK_CONTAINER(Widget);
	ToolButton = GTK_TOOL_BUTTON(ToolItem);
}

GTKToolButton::~GTKToolButton()
{
	delete Icon;
}
