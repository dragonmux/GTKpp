/*
 * This file is part of GTK++ (libGTK++)
 * Copyright © 2012 Richard/Rachel Mant (dx-mon@users.sourceforge.net)
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

GTKDrawingArea::GTKDrawingArea(int Width, int Height) : GTKWidget(gtk_drawing_area_new())
{
	DrawingArea = GTK_DRAWING_AREA(Widget);
	gtk_drawing_area_size(DrawingArea, Width, Height);
}

void GTKDrawingArea::SetSize(int Width, int Height)
{
	gtk_drawing_area_size(DrawingArea, Width, Height);
}
