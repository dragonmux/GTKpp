#include "stdafx.h"

GTKMenuItem::GTKMenuItem(const char *Value) : GTKContainer(gtk_menu_item_new_with_mnemonic(Value))
{
	MenuItem = GTK_MENU_ITEM(Container);
	//gtk_menu_item_set_use_underline(MenuItem, TRUE);
	SetMenuText(Value);
}

void GTKMenuItem::SetMenuText(const char *Value)
{
	if (Value == NULL)
		return;

	//gtk_menu_item_set_label(MenuItem, Value);
}

void GTKMenuItem::SetChildMenu(GTKMenu *Menu)
{
	gtk_menu_item_set_submenu(MenuItem, Menu->GetWidget());
}

void GTKMenuItem::SetOnClicked(void *OnClickFunc, void *data)
{
	SetHandler("activate", OnClickFunc, (data == NULL ? this : data));
}
