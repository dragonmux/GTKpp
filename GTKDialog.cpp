#include "stdafx.h"

/***************************************************************\
|*                   GTKDialog implementation                  *|
\***************************************************************/

GTKDialog::GTKDialog(GtkWidget *Widget) : GTKWidget(Widget)
{
	Dialog = GTK_DIALOG(Widget);
}

int GTKDialog::Run()
{
	return gtk_dialog_run(Dialog);
}
