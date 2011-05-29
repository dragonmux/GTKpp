#include "Globals.h"
#include "GTK++.h"

GTKCheckBox::GTKCheckBox(int Width, int Height, const char *Content)
{
	Widget = gtk_check_button_new();
	Button = GTK_BUTTON(Widget);
	CheckButton = GTK_CHECK_BUTTON(Button);
	if (Content != NULL)
	{
		gtk_button_set_label(Button, Content);
		gtk_button_set_use_underline(Button, TRUE);
	}
}

bool GTKCheckBox::GetChecked()
{
	return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Button));
}

void GTKCheckBox::SetChecked(bool Checked)
{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(Button), Checked);
}
