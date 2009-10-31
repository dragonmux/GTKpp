#include "Globals.h"
#include "GTK++.h"

/***************************************************************\
|*                   GTKDialog implementation                  *|
\***************************************************************/

int GTKDialog::Run()
{
	return gtk_dialog_run(Dialog);
}