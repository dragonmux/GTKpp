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

GTKCheckBox::GTKCheckBox(int , int, const char *Content) : GTKButton(gtk_check_button_new())
{
	CheckButton = GTK_CHECK_BUTTON(Button);
	if (Content != NULL)
	{
		gtk_button_set_label(Button, Content);
		gtk_button_set_use_underline(Button, TRUE);
	}
}

bool GTKCheckBox::GetChecked()
{
	return (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Button)) == FALSE ? false : true);
}

void GTKCheckBox::SetChecked(bool Checked)
{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Button), Checked);
}
