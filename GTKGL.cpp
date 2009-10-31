#include "Globals.h"
#include "GTK++.h"

/***************************************************************\
|*                     GTKGL implementation                    *|
\***************************************************************/

void GTKGL::GTKInit(int argc, char **argv)
{
	GTK::GTKInit(argc, argv);
	gtk_gl_init(&argc, &argv);
}