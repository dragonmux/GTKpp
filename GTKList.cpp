#include "Globals.h"
#include "GTK++.h"

#include <stdio.h>

GTKList::GTKList(GTKWidget *Parent, int Width, int Height, bool NeedsParenting)
{
	Renderer = gtk_cell_renderer_text_new();
	Column = gtk_tree_view_column_new();
	ListStore = gtk_list_store_new(1, G_TYPE_STRING);
	Widget = gtk_tree_view_new_with_model(GTK_TREE_MODEL(ListStore));
	Container = GTK_CONTAINER(Widget);
	ListView = GTK_TREE_VIEW(Container);
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
	OK = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(ListStore), &Iter);
	while (OK != FALSE)
	{
		gtk_tree_model_get(GTK_TREE_MODEL(ListStore), &Iter, 0, &val, -1);
		if (strcmp(Value, val) == 0)
		{
			g_free(val);
			gtk_list_store_remove(ListStore, &Iter);
			break;
		}
		g_free(val);
		OK = gtk_tree_model_iter_next(GTK_TREE_MODEL(ListStore), &Iter);
	}
}

void GTKList::Clear()
{
	bool OK;
	GtkTreeIter Iter = {0};
	do
	{
		OK = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(ListStore), &Iter);
		if (OK != FALSE)
			gtk_list_store_remove(ListStore, &Iter);
	}
	while (OK != FALSE);
}
