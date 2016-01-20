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

GTKColourSelectionDialog::GTKColourSelectionDialog() : GTKDialog(gtk_color_selection_dialog_new("Please pick a colour"))
{
	Selector = GTK_COLOR_SELECTION_DIALOG(Dialog);
	g_signal_connect(GTK_OBJECT(Selector->ok_button), "clicked", G_CALLBACK(OkClicked), this);
	g_signal_connect(GTK_OBJECT(Selector->cancel_button), "clicked", G_CALLBACK(CancelClicked), this);
}

void GTKColourSelectionDialog::SetColour(uint8_t R, uint8_t G, uint8_t B)
{
	GdkColor col = {0, extendColour(R), extendColour(G), extendColour(B)};
	gtk_color_selection_set_current_color(GTK_COLOR_SELECTION(Selector->colorsel), &col);
}

void GTKColourSelectionDialog::GetColour(char *R, char *G, char *B)
{
	GdkColor col;
	gtk_color_selection_get_current_color(GTK_COLOR_SELECTION(Selector->colorsel), &col);
	*R = round(double(col.red) / 257.0);
	*G = round(double(col.green) / 257.0);
	*B = round(double(col.blue) / 257.0);
}

void GTKColourSelectionDialog::OkClicked(GtkWidget *, void *data)
{
	GTKColourSelectionDialog *self = (GTKColourSelectionDialog *)data;
	gtk_dialog_response(self->Dialog, GTK_RESPONSE_OK);
}

void GTKColourSelectionDialog::CancelClicked(GtkWidget *, void *data)
{
	GTKColourSelectionDialog *self = (GTKColourSelectionDialog *)data;
	gtk_dialog_response(self->Dialog, GTK_RESPONSE_CANCEL);
}
