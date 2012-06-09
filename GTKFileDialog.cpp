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
