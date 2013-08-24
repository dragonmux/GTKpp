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

GTKRange::GTKRange(GtkWidget *Widget) : GTKWidget(Widget), StartVal(0)
{
	Range = GTK_RANGE(Widget);
	OnChangedCallbacks.clear();
}

void GTKRange::SetHandlers()
{
	SetHandler("button-press-event", (void *)ButtonPress, this);
	SetHandler("button-release-event", (void *)ButtonRelease, this);
	SetHandler("key-press-event", (void *)KeyPress, this);
	SetHandler("key-release-event", (void *)KeyRelease, this);
	SetHandler("scroll-event", (void *)Scroll, this);
}

GTKRange::~GTKRange()
{
}

double GTKRange::GetValue()
{
	return gtk_range_get_value(Range);
}

void GTKRange::SetValue(double Value)
{
	gtk_range_set_value(Range, Value);
}

bool GTKRange::ButtonPress(GtkWidget *, GdkEventButton *event, void *data)
{
	if (event->button == 1)
	{
		GTKRange *self = (GTKRange *)data;
		self->StartVal = self->GetValue();
	}
	return false;
}

bool GTKRange::ButtonRelease(GtkWidget *, GdkEventButton *event, void *data)
{
	if (event->button == 1)
	{
		GTKRange *self = (GTKRange *)data;
		if (self->StartVal != self->GetValue())
			self->CallOnChangedCallbacks();
	}
	return false;
}

bool GTKRange::KeyPress(GtkWidget *, GdkEventKey *, void *data)
{
	GTKRange *self = (GTKRange *)data;
	self->StartVal = self->GetValue();
	return false;
}

bool GTKRange::KeyRelease(GtkWidget *, GdkEventKey *, void *data)
{
	GTKRange *self = (GTKRange *)data;
	if (self->StartVal != self->GetValue())
		self->CallOnChangedCallbacks();
	return false;
}

bool GTKRange::Scroll(GtkWidget *widget, GdkEventScroll *, void *data)
{
	((GTKRange *)data)->CallOnChangedCallbacks();
	return false;
}

void GTKRange::SetOnChanged(ChangedCallback OnChangedFunc, void *data)
{
	std::pair<ChangedCallback, void *> callback(OnChangedFunc, data);
	OnChangedCallbacks.push_back(callback);
}

void GTKRange::CallOnChangedCallbacks()
{
	size_t i;
	double value = GetValue();
	for (i = 0; i < OnChangedCallbacks.size(); i++)
	{
		std::pair<ChangedCallback, void *> callback = OnChangedCallbacks[i];
		(*callback.first)(callback.second, value);
	}
}

void GTKRange::SetIncrement(double Step)
{
	gtk_range_set_increments(Range, Step, Step * 10.0);
}

void GTKRange::SetIncrement(double Step, double Page)
{
	gtk_range_set_increments(Range, Step, Page);
}
