#include "Globals.h"
#include "GTK++.h"

GTKMenuBar::GTKMenuBar(GTKWidget *Parent, BOOL NeedsParenting)
{
	Widget = gtk_menu_bar_new();
	Container = GTK_CONTAINER(Widget);
	MenuShell = GTK_MENU_SHELL(Container);
	MenuBar = GTK_MENU_BAR(MenuShell);
	if (NeedsParenting != FALSE)
		((GTKContainer *)Parent)->AddChild(this);
}
