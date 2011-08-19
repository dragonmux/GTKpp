#include "Globals.h"
#include "GTK++.h"
#ifdef _WINDOWS
int round(double a)
{
	int b = (int)a;
	if ((a - (double)b) >= 0.5)
		return b + 1;
	return b;
}
#else
#include <math.h>
#endif

GTKColourSelectionDialog::GTKColourSelectionDialog()
{
	Widget = gtk_color_selection_dialog_new("Please pick a colour");
	Dialog = GTK_DIALOG(Widget);
	Selector = GTK_COLOR_SELECTION_DIALOG(Dialog);
	g_signal_connect(GTK_OBJECT(Selector->ok_button), "clicked", G_CALLBACK(OkClicked), this);
	g_signal_connect(GTK_OBJECT(Selector->cancel_button), "clicked", G_CALLBACK(CancelClicked), this);
}

void GTKColourSelectionDialog::SetColour(char R, char G, char B)
{
	GdkColor col = {0, ((int)R) * 257, ((int)G) * 257, ((int)B) * 257};
	gtk_color_selection_set_current_color(GTK_COLOR_SELECTION(Selector->colorsel), &col);
}

void GTKColourSelectionDialog::GetColour(char *R, char *G, char *B)
{
	GdkColor col;
	gtk_color_selection_get_current_color(GTK_COLOR_SELECTION(Selector->colorsel), &col);
	*R = round((double)col.red / 257.0);
	*G = round((double)col.green / 257.0);
	*B = round((double)col.blue / 257.0);
}

void GTKColourSelectionDialog::OkClicked(GtkWidget *widget, void *data)
{
	GTKColourSelectionDialog *self = (GTKColourSelectionDialog *)data;
	gtk_dialog_response(self->Dialog, GTK_RESPONSE_OK);
}

void GTKColourSelectionDialog::CancelClicked(GtkWidget *widget, void *data)
{
	GTKColourSelectionDialog *self = (GTKColourSelectionDialog *)data;
	gtk_dialog_response(self->Dialog, GTK_RESPONSE_CANCEL);
}
