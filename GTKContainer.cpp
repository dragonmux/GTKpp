#include "Globals.h"
#include "GTK++.h"

GTKContainer::GTKContainer()
{
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
	gtk_container_add(Container, (GtkWidget *)Child->GetWidget());
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
	gtk_container_remove(Container, (GtkWidget *)Child->GetWidget());
	Children.erase(i);
}