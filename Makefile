GCC ?= gcc
CC = $(GCC)
EXTRA_CFLAGS = $(shell pkg-config --cflags gtk+-2.0 pango gtkglext-1.0)
CFLAGS = -O2 -g -c -D__GTKpp_EXPORT__ -I./include/ -I./ $(EXTRA_CFLAGS) -o $*.o
LIBS = `pkg-config --libs gtk+-2.0 pango gtkglext-1.0`
LFLAGS = -shared $(O) $(LIBS) -Wl,-soname,$(SO_out) -o $(SO)
AR = ar cr
RANLIB = ranlib

O = GTK.o GTKGL.o GTKWidget.o GTKGLWidget.o GTKWindow.o GTKGLWindow.o GTKFrame.o GTKDialog.o GTKFileDialog.o GTKMessageBox.o GTKFont.o GDKPixbuf.o GTKHBox.o GTKVBox.o GTKKey.o GTKFixed.o GTKButton.o GTKEntry.o GTKImage.o GTKLabel.o GTKHUpDown.o GTKContainer.o GTKEvents.o GTKScrolledWindow.o GTKTextBuffer.o GTKTextView.o GTKList.o GTKCheckBox.o GTKComboBox.o GTKColourSelectionDialog.o GTKAboutDialog.o GTKDrawingArea.o GTKGLDrawingArea.o GTKMenu.o GTKMenuBar.o GTKMenuItem.o GTKMenuShell.o
SO = bin/libGTK++.so
SO_out = libGTK++.so
A = bin/libGTK++.a
LA = bin/libGTK++.la
PC = bin/libGTK++.pc.in

default: all

all: $(O) $(SO) $(LA) $(PC)

install: all
	@cd bin && $(MAKE) install
	@cd include && $(MAKE) install

bin/libGTK++.so:
	rm -f $(SO) $(A)
	$(AR) $(A) $(O)
	$(RANLIB) $(A)
	$(CC) $(LFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $*.cpp

clean: clean-recursive
	rm -f *.o *~

clean-recursive:
	@cd include && $(MAKE) clean
	@cd bin && $(MAKE) clean

GTK.o: GTK.cpp
GTKGL.o: GTKGL.cpp
GTK.o: GTKWidget.cpp
GTKGL.o: GTKGLWidget.cpp
GTK.o: GTKWindow.cpp
GTKGL.o: GTKGLWindow.cpp
GTKFrame.o: GTKFrame.cpp
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
