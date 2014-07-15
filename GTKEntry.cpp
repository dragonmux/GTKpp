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

GTKEntry::GTKEntry(int Width, int Height, const char *Content) : GTKWidget(gtk_entry_new())
{
	Entry = GTK_ENTRY(Widget);
	SetText(Content);
	gtk_widget_set_size_request(Widget, Width, Height);
}

void GTKEntry::SetText(const char *Content)
{
	gtk_entry_set_text(Entry, Content);
}

uint32_t GTKEntry::GetTextLen()
{
	return gtk_entry_get_text_length(Entry);
}

void GTKEntry::GetText(char *Buff, uint32_t BuffLen)
{
	const char *Text = gtk_entry_get_text(Entry);
	if (Text != NULL)
	{
		uint32_t Len = gtk_entry_get_text_length(Entry);
		memcpy(Buff, Text, (Len > BuffLen ? BuffLen : Len));
		if (BuffLen > 0)
			Buff[BuffLen - 1] = 0;
	}
	else
		Buff[0] = 0;
}

inline bool isNumber(const char x)
{
	return x >= '0' && x <= '9';
}

inline bool isMinus(const char x)
{
	return x == '-';
}

inline bool checkNumber(const char *num, uint32_t numLen)
{
	for (uint32_t i = 0; i < numLen; i++)
	{
		if (!isNumber(num[i]))
			return false;
	}
	return true;
}

bool GTKEntry::GetIntValue(int32_t &val)
{
	const char *strNum = gtk_entry_get_text(Entry);
	uint32_t strNumLen = gtk_entry_get_text_length(Entry);
	bool sign = isMinus(strNum[0]);
	if (!checkNumber(strNum + (sign ? 1 : 0), strNumLen - (sign ? 1 : 0)))
		return false;
	val = 0;
	for (uint32_t i = (sign ? 1 : 0); i < strNumLen; i++)
	{
		val *= 10;
		val += strNum[i] - '0';
	}
	if (sign)
		val = -val;
	return true;
}

bool GTKEntry::GetUintValue(uint32_t &val)
{
	const char *strNum = gtk_entry_get_text(Entry);
	uint32_t strNumLen = gtk_entry_get_text_length(Entry);
	if (!checkNumber(strNum, strNumLen))
		return false;
	val = 0;
	for (uint32_t i = 0; i < strNumLen; i++)
	{
		val *= 10;
		val += strNum[i] - '0';
	}
	return true;
}

/*void GTKEntry::SetForegroundColour(int R, int G, int B)
{
	pango_layout_set_font_description
}*/
