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

GTKScale::GTKScale(GtkWidget *Widget) : GTKRange(Widget)
{
	Scale = GTK_SCALE(Range);
}

GTKScale::~GTKScale()
{
}

void GTKScale::SetDecimalPrecision(uint32_t Places)
{
	gtk_scale_set_digits(Scale, Places);
}

void GTKScale::SetValueDrawn(bool Drawn)
{
	gtk_scale_set_draw_value(Scale, (Drawn ? TRUE : FALSE));
}

void GTKScale::SetValuePosition(GtkPositionType Position)
{
	gtk_scale_set_value_pos(Scale, Position);
}

void GTKScale::AddMark(double MarkValue, GtkPositionType MarkPosition, const char *MarkText)
{
	gtk_scale_add_mark(Scale, MarkValue, MarkPosition, MarkText);
}

void GTKScale::ClearAllMarks()
{
	gtk_scale_clear_marks(Scale);
}
