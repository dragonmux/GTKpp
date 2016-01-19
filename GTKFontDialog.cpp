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

GTKFontDialog::GTKFontDialog(const char *Title) : GTKDialog(gtk_font_selection_dialog_new(Title))
{
	FontDialog = GTK_FONT_SELECTION_DIALOG(Dialog);
	FontSelection = GTK_FONT_SELECTION(gtk_font_selection_dialog_get_font_selection(FontDialog));
}

void GTKFontDialog::SetFontName(const char *Font)
{
	gtk_font_selection_dialog_set_font_name(FontDialog, Font);
}

char *GTKFontDialog::GetFontName()
{
	return gtk_font_selection_dialog_get_font_name(FontDialog);
}

int32_t GTKFontDialog::GetFontSize()
{
	return gtk_font_selection_get_size(FontSelection);
}
