#include "Globals.h"
#include "GTK++.h"

GTKProgressBar::GTKProgressBar()
{
	Widget = gtk_progress_bar_new();
	ProgressBar = GTK_PROGRESS_BAR(Widget);
	gtk_progress_bar_set_pulse_step(ProgressBar, 0.05);
	gtk_progress_bar_pulse(ProgressBar);
	Max = Progress = 0;
}

GTKProgressBar::GTKProgressBar(int Max)
{
	if (Max < 1)
		return;
	Widget = gtk_progress_bar_new();
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