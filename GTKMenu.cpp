#include "Globals.h"
#include "GTK++.h"

GTKMenu::GTKMenu(GTKWidget *Parent, BOOL NeedsParenting)
{
	Widget = gtk_menu_new();
	Container = GTK_CONTAINER(Widget);
	MenuShell = GTK_MENU_SHELL(Container);
	Menu = GTK_MENU(MenuShell);
}