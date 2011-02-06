#include "Globals.h"
#include "GTK++.h"

void GTKMenuShell::AddChild(GTKWidget *Child)
{
	AddChild(Child, TRUE);
}

void GTKMenuShell::AddChild(GTKWidget *Child, BOOL Append)
{
	if (Append != FALSE)
		gtk_menu_shell_append(MenuShell, (GtkWidget *)Child->GetWidget());
	else
		gtk_menu_shell_prepend(MenuShell, (GtkWidget *)Child->GetWidget());
	Children.push_back(Child);
}