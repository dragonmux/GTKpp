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

/***************************************************************\
|*                    GTKImage implementation                  *|
\***************************************************************/

GTKComboBox::GTKComboBox(GTKWidget *Parent, int Width, int Height, bool NeedsParenting) : GTKContainer(gtk_combo_box_new_text())
{
	ComboBox = GTK_COMBO_BOX(Container);
	lastPos = -1;
	if (NeedsParenting != FALSE)
		SetParent(Parent);
	gtk_widget_set_size_request(Widget, Width, Height);
}

GTKComboBox::~GTKComboBox()
{
	while (Items.size() != 0)
	{
		std::map<int, GTKComboBoxEntry>::iterator i = Items.end()--;
		(*i).second.FreeFn((void *)((*i).second.Text));
		Items.erase(i);
	}
}

void GTKComboBox::SetParent(GTKWidget *Parent)
{
	((GTKContainer *)Parent)->AddChild(this);
}

void GTKComboBox::AddItem(const char *Text, int EnumValue, freeFn FreeFn)
{
	if (Items.find(EnumValue) != Items.end())
	{
		printf("Error, cannot insert duplicate value to list with Enumerator value %i\n", EnumValue);
		return;
	}
	else
	{
		Items[EnumValue].Text = Text;
		Items[EnumValue].ComboPos = ++lastPos;
		Items[EnumValue].FreeFn = FreeFn;
	}
	gtk_combo_box_append_text(ComboBox, Text);
}

void GTKComboBox::DeleteItem(const char *Text)
{
	int a = getPossitionOf(Text);
	if (a == -1)
		return;
	gtk_combo_box_remove_text(ComboBox, Items[a].ComboPos);
}

void GTKComboBox::SetSelected(const char *Text)
{
	gtk_combo_box_set_active(ComboBox, getPossitionOf(Text));
}

void GTKComboBox::SetSelected(unsigned int EnumValue)
{
	if (getTextFor(EnumValue) == NULL)
		return;
	gtk_combo_box_set_active(ComboBox, Items[EnumValue].ComboPos);
}

int GTKComboBox::GetSelected()
{
	return getEnumFor(gtk_combo_box_get_active(ComboBox));
}

const char *GTKComboBox::getTextFor(unsigned int Value)
{
	if (Items.find(Value) == Items.end())
		return NULL;
	else
		return Items[Value].Text;
}

int GTKComboBox::getPossitionOf(const char *Value)
{
	std::map<int, GTKComboBoxEntry>::iterator i;
	for (i = Items.begin(); i != Items.end(); i++)
	{
		if (strcmp((*i).second.Text, Value) == 0)
			return (*i).second.ComboPos;
	}
	return -1;
}

int GTKComboBox::getEnumFor(unsigned int Value)
{
	std::map<int, GTKComboBoxEntry>::iterator i;
	if (Value == -1)
		return Value;
	for (i = Items.begin(); i != Items.end(); i++)
	{
		if ((*i).second.ComboPos == Value)
			return (*i).first;
	}
	return -1;
}
