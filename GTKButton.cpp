#include "stdafx.h"

GTKButton::GTKButton(const char *Content)
{
	Widget = gtk_button_new();
	Button = GTK_BUTTON(Widget);
	if (Content != NULL)
	{
		gtk_button_set_label(Button, Content);
		gtk_button_set_use_underline(Button, TRUE);
	}
}

void GTKButton::SetSize(int Width, int Height)
{
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKButton::SetImage(GtkWidget *Image)
{
	gtk_button_set_image(Button, Image);
}

void GTKButton::SetOnClicked(void *OnClickFunc, void *data)
{
	SetHandler("clicked", OnClickFunc, (data == NULL ? this : data));
}
