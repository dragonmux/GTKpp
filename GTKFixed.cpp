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

GTKFixed::GTKFixed(GTKWidget *Parent, int Width, int Height) : GTKContainer(gtk_fixed_new())
{
	//GtkStyle *Style = gtk_style_new();
	Fixed = GTK_FIXED(Container);
	SetParent(Parent);
	/*gtk_style_set_font(Style, gdk_font_load("Courier New"));
	gtk_widget_set_style(Widget, Style);*/
	gtk_widget_set_size_request(Widget, Width, Height);
}

GTKFixed::GTKFixed(int Width, int Height) : GTKContainer(gtk_fixed_new())
{
	Fixed = GTK_FIXED(Container);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKFixed::SetParent(GTKWidget *Parent)
{
	((GTKContainer *)Parent)->AddChild(this);
}

void GTKFixed::SetLocation(GTKWidget *ChildWidget, int X, int Y)
{
	gtk_fixed_put(Fixed, ChildWidget->GetWidget(), X, Y);
	Children.push_back(ChildWidget);
}

void GTKFixed::SetMove(GTKWidget *ChildWidget, int X, int Y)
{
	gtk_fixed_move(Fixed, ChildWidget->GetWidget(), X, Y);
}

void GTKFixed::SetSize(int Width, int Height)
{
	gtk_widget_set_size_request(Widget, Width, Height);
}
