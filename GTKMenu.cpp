#include "stdafx.h"

GTKMenu::GTKMenu(GTKWidget *Parent, bool NeedsParenting) : GTKMenuShell(gtk_menu_new())
{
	Menu = GTK_MENU(MenuShell);
}
