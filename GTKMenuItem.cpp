/*
 * This file is part of GTK++ (libGTK++)
 * Copyright © 2012 Rachel Mant (dx-mon@users.sourceforge.net)
 *
 * GTK++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GTK++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

GTKMenuSeparatorItem::GTKMenuSeparatorItem() : GTKContainer(gtk_separator_menu_item_new())
{
}
