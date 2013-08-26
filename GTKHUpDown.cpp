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
#include "img/ArrowLeft.h"
#include "img/ArrowRight.h"

GTKHUpDown::GTKHUpDown(int Width, int Height, void *IncrementFunc, void *DecrementFunc, void *data) : GTKHBox(Width, Height, true, 0)
{
	GdkPixbuf *Pixbuf;
	GtkWidget *Image;
	Left = new GTKButton();
	Right = new GTKButton();
	AddChild(Left);
	AddChild(Right);
	Pixbuf = gdk_pixbuf_new_from_inline(-1, ArrowLeft, FALSE, NULL);
	Image = gtk_image_new_from_pixbuf(Pixbuf);
	g_object_unref(Pixbuf);
	Left->SetImage(Image);
	Pixbuf = gdk_pixbuf_new_from_inline(-1, ArrowRight, FALSE, NULL);
	Image = gtk_image_new_from_pixbuf(Pixbuf);
	g_object_unref(Pixbuf);
	Right->SetImage(Image);
	Current = Min = Max = 0;
	Left->SetOnClicked(DecrementFunc, data);
	Right->SetOnClicked(IncrementFunc, data);
}

void GTKHUpDown::SetRange(int Min, int Max)
{
	this->Min = Min;
	this->Max = Max;
}

int GTKHUpDown::GetPos()
{
	return Current;
}

void GTKHUpDown::SetPos(int Pos)
{
	if (Pos > Max)
		Current = Max;
	else if (Pos < Min)
		Current = Min;
	else
		Current = Pos;
}
