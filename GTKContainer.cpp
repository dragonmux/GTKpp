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

GTKContainer::GTKContainer(GtkWidget *Widget) : GTKWidget(Widget)
{
	Container = GTK_CONTAINER(Widget);
	Children.clear();
}

GTKContainer::~GTKContainer()
{
	while (Children.size() != 0)
	{
		delete Children.back();
		Children.pop_back();
	}
}

void GTKContainer::AddChild(GTKWidget *Child)
{
	gtk_container_add(Container, Child->GetWidget());
	Children.push_back(Child);
}

void GTKContainer::RemoveChild(GTKWidget *Child)
{
	std::list<GTKWidget *>::iterator i = Children.begin();
	do
	{
		if (i == Children.end())
			return;
		if (*i == Child)
			break;
	}
	while (i++, true);
	gtk_container_remove(Container, Child->GetWidget());
	Children.erase(i);
}

void GTKContainer::SetBorder(int BorderWidth)
{
	gtk_container_set_border_width(Container, BorderWidth);
}
