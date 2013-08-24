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

GTKScrolledWindow::GTKScrolledWindow(GTKWidget *Parent, int Width, int Height, bool NeedsParenting) : GTKContainer(gtk_scrolled_window_new(NULL, NULL))
{
	ScrolledWindow = GTK_SCROLLED_WINDOW(Container);
	if (NeedsParenting == true)
		SetParent(Parent);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKScrolledWindow::SetParent(GTKWidget *Parent)
{
	((GTKContainer *)Parent)->AddChild(this);
}

void GTKScrolledWindow::AddChild(GTKWidget *Child)
{
	gtk_container_add(Container, Child->GetWidget());
}
