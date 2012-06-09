#include "stdafx.h"

GTKMenuBar::GTKMenuBar(GTKWidget *Parent, bool NeedsParenting) : GTKMenuShell(gtk_menu_bar_new())
{
	MenuBar = GTK_MENU_BAR(MenuShell);
	if (NeedsParenting == true)
		((GTKContainer *)Parent)->AddChild(this);
}
