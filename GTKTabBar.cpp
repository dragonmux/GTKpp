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

GTKTabBar::GTKTabBar() : GTKContainer(gtk_notebook_new())
{
	TabBar = GTK_NOTEBOOK(Container);
	Labels.clear();
}

GTKTabBar::~GTKTabBar()
{
	while (Labels.size() != 0)
	{
		delete Labels.back();
		Labels.pop_back();
	}
}

void GTKTabBar::AppendPage(GTKWidget *Child, const char *Label)
{
	GTKWidget *label = new GTKLabel(Label);
	AppendPage(Child, label);
}

void GTKTabBar::AppendPage(GTKWidget *Child, GTKWidget *Label)
{
	gtk_notebook_append_page(TabBar, Child->GetWidget(), Label->GetWidget());
	Children.push_back(Child);
	Labels.push_back(Label);
}

void GTKTabBar::RemovePage(GTKWidget *Child)
{
	std::list<GTKWidget *>::iterator i = Children.begin();
	int32_t pageNum = gtk_notebook_page_num(TabBar, Child->GetWidget());
	if (pageNum == -1)
		return;

	gtk_notebook_remove_page(TabBar, pageNum);
	delete Labels[pageNum];
	Labels.erase(Labels.begin() + pageNum);

	while (i != Children.end())
	{
		if (*i == Child)
			break;
	}
	if (i == Children.end())
		return;
	Children.erase(i);
}
