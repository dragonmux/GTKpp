#include "Globals.h"
#include "GTK++.h"

GTKMenuBar::GTKMenuBar(GTKWidget *Parent, bool NeedsParenting)
{
	Widget = gtk_menu_bar_new();
	Container = GTK_CONTAINER(Widget);
	MenuShell = GTK_MENU_SHELL(Container);
	MenuBar = GTK_MENU_BAR(MenuShell);
	if (NeedsParenting == true)
		((GTKContainer *)Parent)->AddChild(this);
}
