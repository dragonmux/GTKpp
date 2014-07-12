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

GTKTree::GTKTree() : GTKContainer(gtk_tree_view_new())
{
	Renderer = gtk_cell_renderer_text_new();
	Column = gtk_tree_view_column_new();
	TreeView = GTK_TREE_VIEW(Container);
	TreeStore = gtk_tree_store_new(1, G_TYPE_STRING);
	gtk_tree_view_set_model(TreeView, GTK_TREE_MODEL(TreeStore));
	gtk_tree_view_column_set_visible(Column, TRUE);
	gtk_tree_view_column_pack_start(Column, Renderer, TRUE);
	gtk_tree_view_column_set_attributes(Column, Renderer, "text", 0, NULL);
	gtk_tree_view_append_column(TreeView, Column);
	gtk_tree_view_set_headers_visible(TreeView, FALSE);
}

GTKTree::~GTKTree()
{
	for (nodeIter i = Nodes.begin(); i != Nodes.end(); i++)
		delete *i;
}

void *GTKTree::AddItem(const char *Value, void *Parent)
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

void GTKTree::RemoveItem(void *Node)
{
	GtkTreeIter *Iter = (GtkTreeIter *)Node;
	if (Node == NULL || Nodes.find(Iter) == Nodes.end())
		return;

	RemoveSubItems(Node);
	gtk_tree_store_remove(TreeStore, Iter);
	Nodes.erase(Iter);
}

void GTKTree::RemoveSubItems(void *Node)
{
	GtkTreeIter *Iter, *ParentIter = (GtkTreeIter *)Node;
	if (Node != NULL && Nodes.find(ParentIter) == Nodes.end())
		return;

	while (gtk_tree_model_iter_children(GTK_TREE_MODEL(TreeStore), Iter, ParentIter) != FALSE)
		RemoveItem(Iter);
}

bool GTKTreeIterComp::operator ()(GtkTreeIter *x, GtkTreeIter *y) const
{
	return x->stamp < y->stamp;
}
