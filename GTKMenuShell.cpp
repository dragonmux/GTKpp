#include "stdafx.h"

void GTKMenuShell::AddChild(GTKWidget *Child, bool Append)
{
	if (Append == true)
		gtk_menu_shell_append(MenuShell, Child->GetWidget());
	else
		gtk_menu_shell_prepend(MenuShell, Child->GetWidget());
	Children.push_back(Child);
}
