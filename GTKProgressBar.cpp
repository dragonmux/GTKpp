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

GTKProgressBar::GTKProgressBar() : GTKWidget(gtk_progress_bar_new())
{
	ProgressBar = GTK_PROGRESS_BAR(Widget);
	gtk_progress_bar_set_pulse_step(ProgressBar, 0.05);
	gtk_progress_bar_pulse(ProgressBar);
	Max = Progress = 0;
}

GTKProgressBar::GTKProgressBar(int Max) : GTKWidget(gtk_progress_bar_new())
{
	if (Max < 1)
		throw (void *)NULL;
	ProgressBar = GTK_PROGRESS_BAR(Widget);
	this->Max = Max;
	Reset();
}

void GTKProgressBar::Reset()
{
	Progress = 0;
	gtk_progress_bar_set_fraction(ProgressBar, 0.0);
}

void GTKProgressBar::Increment()
{
	if (Progress < Max)
		Progress++;
	gtk_progress_bar_set_fraction(ProgressBar, ((double)Progress)/((double)Max));
}

void GTKProgressBar::Pulse()
{
	gtk_progress_bar_pulse(ProgressBar);
}

void GTKProgressBar::SetMax(int Max)
{
	if (Max < 1)
		return;
	if (Progress > Max)
		Progress = Max;
	this->Max = Max;
	gtk_progress_bar_set_fraction(ProgressBar, ((double)Progress)/((double)Max));
}

void GTKProgressBar::SetProgress(int Progress)
{
	if (Progress < 1)
		return;
	if (Progress > Max)
		Progress = Max;
	this->Progress = Progress;
	gtk_progress_bar_set_fraction(ProgressBar, ((double)Progress)/((double)Max));
}
