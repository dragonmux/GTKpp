#include "stdafx.h"

GTKMenuShell::GTKMenuShell(GtkWidget *Widget) : GTKContainer(Widget)
{
	MenuShell = GTK_MENU_SHELL(Container);
}

void GTKMenuShell::AddChild(GTKWidget *Child, bool Append)
{
	if (Append == true)
		gtk_menu_shell_append(MenuShell, Child->GetWidget());
	else
		gtk_menu_shell_prepend(MenuShell, Child->GetWidget());
	Children.push_back(Child);
}
