# This file is part of GTK++ (libGTK++)
# Copyright © 2012 Rachel Mant (dx-mon@users.sourceforge.net)
#
# GTK++ is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# GTK++ is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
include Makefile.inc

PKG_CONFIG = gtk+-2.0 pango $(PKG_GL)
EXTRA_CFLAGS = $(shell pkg-config --cflags $(PKG_CONFIG)) $(CFLAGS_GL)
DEFS = -Wall -Wextra -pedantic -D__GTKpp_EXPORT__ -Iinclude
CFLAGS = $(OPTIM_FLAGS) -c $(DEFS) $(EXTRA_CFLAGS) -o $@ $<
DEPFLAGS = $(OPTIM_FLAGS) -E -MM $(DEFS) $(EXTRA_CFLAGS) -o .dep/$*.d $<
LIBS = $(shell pkg-config --libs $(PKG_CONFIG)) -lstdc++ -lm
LFLAGS = $(OPTIM_FLAGS) -shared $(O) $(LIBS) -Wl,-soname,$(SO_out) -z defs -o $(SO)

ifeq ($(strip $(NOGL)), 1)
	O_GL =
	PKG_GL =
	CFLAGS_GL = -D__NO_OPEN_GL__
else
	O_GL = GTKGL.o GLBase.o GTKGLWindow.o GTKFont.o GTKGLDrawingArea.o
	PKG_GL = gtkglext-1.0
	CFLAGS_GL =
endif

O = GTK.o GTKWidget.o GTKWindow.o GTKFrame.o GTKDialog.o GTKFileDialog.o GTKMessageBox.o GDKPixbuf.o GTKBox.o GTKHBox.o GTKVBox.o GTKKey.o GTKFixed.o GTKButton.o GTKEntry.o GTKImage.o GTKLabel.o \
	GTKHUpDown.o GTKContainer.o GTKEvents.o GTKScrolledWindow.o GTKTextBuffer.o GTKTextView.o GTKList.o GTKCheckBox.o GTKComboBox.o GTKColourSelectionDialog.o GTKAboutDialog.o GDKPixmap.o GTKDrawingArea.o \
	GTKCairoDrawingArea.o GTKMenu.o GTKMenuBar.o GTKMenuItem.o GTKMenuShell.o GTKProgressBar.o GTKRange.o GTKScale.o GTKHScale.o GTKVScale.o GTKSeparator.o GTKHSeparator.o GTKVSeparator.o \
	GTKTabBar.o GTKTree.o GTKToolBar.o GTKToolItem.o GTKToolButton.o GTKMisc.o GTKFontDialog.o $(O_GL)
#GTKFixedFrame.o
SO = bin/libGTK++.so
SO_out = libGTK++.so
A = bin/libGTK++.a
PC = bin/libGTK++.pc.in

default: all

all: $(SO)

ifneq ($(strip $(LIBDIR)),)
VARS = LIBDIR=$(LIBDIR)
endif
ifneq ($(strip $(PREFIX)),)
VARS += PREFIX=$(PREFIX)
endif

install: all $(PC)
	$(Q)if [[ $(UID) -ne 0 && "$(PREFIX)" =~ ^/usr\.*\$$ ]]; then \
		sudo make $(VARS) sudo-install; \
	else \
		$(MAKE) sudo-install; \
	fi

sudo-install:
	@cd bin && $(MAKE) install
	@cd include && $(MAKE) install

.dep:
	$(call run-cmd,install_dir,.dep)

bin/libGTK++.so: .dep $(O)
	$(call run-cmd,ar,$(A),$(O))
	$(call run-cmd,ranlib,$(A))
	$(call run-cmd,ccld,$(LFLAGS))
	$(call debug-strip,$(SO))

.cpp.o:
	$(call makedep,$(CXX),$(DEPFLAGS))
	$(call run-cmd,cxx,$(CFLAGS))

clean: .dep clean-recursive
	$(call run-cmd,rm,GTK++,$(O) $(SO_out))
	$(call run-cmd,rm,makedep,.dep/*.d)

clean-recursive:
	@cd bin && $(MAKE) clean

.PHONY: default all install sudo-install .cpp.o clean clean-recursive

# GLPixelFormats.o: GLPixelFormats.cpp # for Windows only!
# GTKAdjustment.o: GTKAdjustment.cpp # not yet, not ready yet.
# GTKViewport.o: GTKViewport.cpp # not yet, not ready yet.
-include .dep/*.d
