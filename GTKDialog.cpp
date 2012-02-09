#include "stdafx.h"

/***************************************************************\
|*                   GTKDialog implementation                  *|
\***************************************************************/

int GTKDialog::Run()
{
	return gtk_dialog_run(Dialog);
}
