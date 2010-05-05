#include "Globals.h"
#include "GTK++.h"
#include "img/ArrowLeft.h"
#include "img/ArrowRight.h"

GTKHUpDown::GTKHUpDown(int Width, int Height, void *IncrementFunc, void *DecrementFunc, void *data) : GTKHBox(Width, Height, TRUE, 0)
{
	GdkPixbuf *Pixbuf;
	GtkWidget *Image;
	Left = new GTKButton();
	Right = new GTKButton();
	AddWidget(Left);
	AddWidget(Right);
	Pixbuf = gdk_pixbuf_new_from_inline(-1, ArrowLeft, FALSE, NULL);
	Image = gtk_image_new_from_pixbuf(Pixbuf);
	gdk_pixbuf_unref(Pixbuf);
	Left->SetImage(Image);
	Pixbuf = gdk_pixbuf_new_from_inline(-1, ArrowRight, FALSE, NULL);
	Image = gtk_image_new_from_pixbuf(Pixbuf);
	gdk_pixbuf_unref(Pixbuf);
	Right->SetImage(Image);
	Current = Min = Max = 0;
	Left->SetOnClicked(DecrementFunc, data);
	Right->SetOnClicked(IncrementFunc, data);
}

void GTKHUpDown::SetRange(int Min, int Max)
{
	this->Min = Min;
	this->Max = Max;
}

int GTKHUpDown::GetPos()
{
	return Current;
}

void GTKHUpDown::SetPos(int Pos)
{
	if (Pos > Max)
		Current = Max;
	else if (Pos < Min)
		Current = Min;
	else
		Current = Pos;
}
