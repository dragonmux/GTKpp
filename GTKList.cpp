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

#include <stdio.h>

GTKList::GTKList(GTKWidget *Parent, int Width, int Height, bool NeedsParenting) : GTKContainer(gtk_tree_view_new())
{
	Renderer = gtk_cell_renderer_text_new();
	Column = gtk_tree_view_column_new();
	ListView = GTK_TREE_VIEW(Container);
	ListStore = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_tree_view_set_model(ListView, GTK_TREE_MODEL(ListStore));
	gtk_tree_view_column_set_visible(Column, TRUE);
	gtk_tree_view_column_pack_start(Column, Renderer, TRUE);
	gtk_tree_view_column_set_attributes(Column, Renderer, "text", 0, NULL);
	gtk_tree_view_append_column(ListView, Column);
	gtk_tree_view_set_headers_visible(ListView, FALSE);
	gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(ListStore), 0, GTK_SORT_ASCENDING);
	if (NeedsParenting != FALSE)
		SetParent(Parent);
	gtk_widget_set_size_request(Widget, Width, Height);
}

// "font-desc" << use this to change the font via a g_object_set(G_OBJECT(Renderer), [attr], [attr_val], NULL); call..

GTKList::~GTKList()
{
	g_object_unref(Column);
//	gtk_tree_view_free(ListView);
}

void GTKList::SetParent(GTKWidget *Parent)
{
	((GTKContainer *)Parent)->AddChild(this);
}

void GTKList::AddItem(char *Value)
{
	GtkTreeIter Iter = {0};
	gtk_list_store_append(ListStore, &Iter);
	gtk_list_store_set(ListStore, &Iter, 0, Value, -1);
}

void GTKList::DeleteItem(char *Value)
{
	bool OK;
	char *val;
	GtkTreeIter Iter = {0};
	OK = (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(ListStore), &Iter) == FALSE ? false : true);
	while (OK == true)
	{
		gtk_tree_model_get(GTK_TREE_MODEL(ListStore), &Iter, 0, &val, -1);
		if (strcmp(Value, val) == 0)
		{
			g_free(val);
			gtk_list_store_remove(ListStore, &Iter);
			break;
		}
		g_free(val);
		OK = (gtk_tree_model_iter_next(GTK_TREE_MODEL(ListStore), &Iter) == FALSE ? false : true);
	}
}

void GTKList::Clear()
{
	bool OK;
	GtkTreeIter Iter = {0};
	do
	{
		OK = (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(ListStore), &Iter) == FALSE ? false : true);
		if (OK != FALSE)
			gtk_list_store_remove(ListStore, &Iter);
	}
	while (OK != FALSE);
}
