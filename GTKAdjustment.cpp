/*
 * This file is part of GTK++ (libGTK++)
 * Copyright © 2012 Richard/Rachel Mant (dx-mon@users.sourceforge.net)
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