#include "Globals.h"
#include "GTK++.h"

/***************************************************************\
|*                  GTKGLWindow implementation                 *|
\***************************************************************/

GTKGLWindow::GTKGLWindow(GtkWindowType Type, GdkGLConfig *Config, void *CloseFunc, int PixFormat, bool AutoRedraw, int Timeout) :
	GTKWindow(Type, CloseFunc), GTKGLWidget(Config, GTKWindow::Widget, PixFormat, AutoRedraw, Timeout)
{
}
