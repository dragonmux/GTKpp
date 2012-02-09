GCC ?= gcc
#GCC_VER = $(shell gcc -dumpversion | cut -d . -f 1)
#ifeq ($(shell if [ $(GCC_VER) -ge 4 ]; then echo 1; else echo 0; fi), 1)
#GCC_FLAGS = -fvisibility=hidden -fvisibility-inlines-hidden
#else
#GCC_FLAGS = 
#endif
GCC_FLAGS = -ggdb
CC = $(GCC) $(GCC_FLAGS)
EXTRA_CFLAGS = $(shell pkg-config --cflags gtk+-2.0 pango gtkglext-1.0)
CFLAGS = -O2 -c -D__GTKpp_EXPORT__ -I./include/ -I./ $(EXTRA_CFLAGS) -o $*.o
LIBS = $(shell pkg-config --libs gtk+-2.0 pango gtkglext-1.0)
LFLAGS = -shared $(O) $(LIBS) -Wl,-soname,$(SO_out) -o $(SO)
AR = ar cr
RANLIB = ranlib
STRIP = strip -x

O = GTK.o GTKGL.o GTKWidget.o GLBase.o GTKWindow.o GTKGLWindow.o GTKFrame.o GTKDialog.o GTKFileDialog.o GTKMessageBox.o GTKFont.o GDKPixbuf.o GTKHBox.o GTKVBox.o GTKKey.o GTKFixed.o GTKButton.o GTKEntry.o GTKImage.o GTKLabel.o GTKHUpDown.o GTKContainer.o GTKEvents.o GTKScrolledWindow.o GTKTextBuffer.o GTKTextView.o GTKList.o GTKCheckBox.o GTKComboBox.o GTKColourSelectionDialog.o GTKAboutDialog.o GTKDrawingArea.o GTKGLDrawingArea.o GTKMenu.o GTKMenuBar.o GTKMenuItem.o GTKMenuShell.o GTKProgressBar.o GTKRange.o GTKScale.o GTKHScale.o GTKVScale.o GTKSeparator.o GTKHSeparator.o GTKVSeparator.o
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

install: all $(PC)
	sudo make $(VARS) sudo-install

sudo-install:
	@cd bin && $(MAKE) install
	@cd include && $(MAKE) install

bin/libGTK++.so: $(O)
	$(AR) $(A) $(O)
	$(RANLIB) $(A)
	$(CC) $(LFLAGS)
#	$(STRIP) $(SO)

.cpp.o:
	$(CC) $(CFLAGS) $*.cpp

clean: clean-recursive
	rm -f *.o *~

clean-recursive:
	@cd include && $(MAKE) clean
	@cd bin && $(MAKE) clean

GTK.o: GTK.cpp
GTKGL.o: GTKGL.cpp
GTKWidgeto: GTKWidget.cpp
GLBase.o: GLBase.cpp
GTKWindow.o: GTKWindow.cpp
GTKGLWindow.o: GTKGLWindow.cpp
GTKFrame.o: GTKFrame.cpp
GTKFixedFrame.o: GTKFixedFrame.cpp
GTKDialog.o: GTKDialog.cpp
GTKFileDialog.o: GTKFileDialog.cpp
GTKMessageBox.o: GTKMessageBox.cpp
GTKFont.o: GTKFont.cpp
GDKPixbuf.o: GDKPixbuf.cpp
GTKHBox.o: GTKHBox.cpp
GTKVBox.o: GTKVBox.cpp
GTKKey.o: GTKKey.cpp
GTKFixed.o: GTKFixed.cpp
GTKButton.o: GTKButton.cpp
GTKEntry.o: GTKEntry.cpp
GTKImage.o: GTKImage.cpp
GTKLabel.o: GTKLabel.cpp
GTKHUpDown.o: GTKHUpDown.cpp
# GLPixelFormats.o: GLPixelFormats.cpp # for Windows only!
GTKContainer.o: GTKContainer.cpp
GTKEvents.o: GTKEvents.cpp
GTKScrolledWindow.o: GTKScrolledWindow.cpp
GTKTextBuffer.o: GTKTextBuffer.cpp
GTKTextView.o: GTKTextView.cpp
GTKList.o: GTKList.cpp
GTKCheckBox.o: GTKCheckBox.cpp
GTKComboBox.o: GTKComboBox.cpp
GTKColourSelectionDialog.o: GTKColourSelectionDialog.cpp
GTKAboutDialog.o: GTKAboutDialog.cpp
# GTKAdjustment.o: GTKAdjustment.cpp # not yet, not ready yet.
GTKDrawingArea.o: GTKDrawingArea.cpp
GTKGLDrawingArea.o: GTKGLDrawingArea.cpp
# GTKViewport.o: GTKViewport.cpp # not yet, not ready yet.
GTKMenu.o: GTKMenu.cpp
GTKMenuBar.o: GTKMenuBar.cpp
GTKMenuItem.o: GTKMenuItem.cpp
GTKMenuShell.o: GTKMenuShell.cpp
GTKProgressBar.o: GTKProgressBar.cpp
GTKRange.o: GTKRange.cpp
GTKScale.o: GTKScale.cpp
GTKHScale.o: GTKHScale.cpp
GTKVScale.o: GTKVScale.cpp
GTKSeparator.o: GTKSeparator.cpp
GTKHSeparator.o: GTKHSeparator.cpp
GTKVSeparator.o: GTKVSeparator.cpp
