#include "stdafx.h"

GTKAdjustment::GTKAdjustment(int Dim, int Unit)
{
	Adjustment = gtk_adjustment_new(0, 0, Dim, Unit, Unit * 4, Dim);
}

/*class GTKAdjustment
{
protected:
	GtkAdjustment *Adjustment;

public:
	GTKpp_API GTKAdjustment(int Dim, int Unit);
	GTKpp_API void Adjust(int newDim);
	GTKpp_API void SrollBy(int Amount);
	GTKpp_API const GtkAdjustment *GetAdjustment();
};*/