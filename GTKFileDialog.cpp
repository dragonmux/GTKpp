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

/***************************************************************\
|*                 GTKFileDialog implementation                *|
\***************************************************************/

GTKFileDialog::GTKFileDialog(GtkWindow *Window, const char *Title, GtkFileChooserAction Action, std::vector<const char *> FileTypes,
	std::vector<const char *> FileTypeNames, const char *Button1_Type, int Button1_Result, const char *Button2_Type, int Button2_Result) :
	GTKDialog(gtk_file_chooser_dialog_new(Title, Window, Action, Button1_Type, Button1_Result, Button2_Type, Button2_Result, NULL))
{
	FileDialog = GTK_FILE_CHOOSER(Dialog);
	gtk_file_chooser_set_do_overwrite_confirmation(FileDialog, TRUE);
	AddFilters(FileTypes, FileTypeNames);
	if (strncmp(Button1_Type, GTK_STOCK_SAVE, 8) == 0 || strncmp(Button2_Type, GTK_STOCK_SAVE, 8) == 0)
		AddFilterChooser(FileTypes, FileTypeNames);
}

void GTKFileDialog::AddFilters(std::vector<const char *> FileTypes, std::vector<const char *> FileTypeNames)
{
	for (uint32_t i = 0; i < FileTypes.size(); i++)
	{
		Filter = gtk_file_filter_new();
		gtk_file_filter_add_pattern(Filter, FileTypes[i]);
		gtk_file_filter_set_name(Filter, FileTypeNames[i]);
		gtk_file_chooser_add_filter(FileDialog, Filter);
		if (i == 0)
			gtk_file_chooser_set_filter(FileDialog, Filter);
	}
}

void GTKFileDialog::AddFilterChooser(std::vector<const char *> FileTypes, std::vector<const char *> FileTypeNames)
{
	/*GtkWidget *dropdown = gtk_combo_box_new();
	GtkComboBox *cboFilters = GTK_COMBO_BOX(dropdown);
	gtk_combo_box_*/
}

char *GTKFileDialog::GetSelectedFile()
{
	return gtk_file_chooser_get_filename(FileDialog);
}
