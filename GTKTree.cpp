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

GTKTree::GTKTree() : GTKContainer(gtk_invisible_new())
{
	g_object_unref(Widget);
	TreeStore = gtk_tree_store_new(1, G_TYPE_STRING);
	Widget = gtk_tree_view_new_with_model(GTK_TREE_MODEL(TreeStore));
	Container = GTK_CONTAINER(Widget);
	TreeView = GTK_TREE_VIEW(Container);
}

GTKTree::~GTKTree()
{
}

void *GTKTree::AddItem(char *Value, void *Parent)
{
	GtkTreeIter *Iter, *ParentIter = (GtkTreeIter *)Parent;
	if (Parent != NULL && Nodes.find(ParentIter) == Nodes.end())
		return NULL;

	Iter = new GtkTreeIter();
	memset(Iter, 0, sizeof(GtkTreeIter));
	gtk_tree_store_append(TreeStore, Iter, ParentIter);
	gtk_tree_store_set(TreeStore, Iter, 0, Value, -1);
	Nodes.insert(Iter);
	return Iter;
}
