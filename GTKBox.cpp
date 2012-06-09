#include "stdafx.h"

GTKBox::GTKBox(GtkWidget *Widget) : GTKContainer(Widget)
{
	Box = GTK_BOX(Container);
}
