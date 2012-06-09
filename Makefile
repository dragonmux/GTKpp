GCC ?= gcc
ifeq ($(strip $(DEBUG)), 1)
	OPTIM_FLAGS = -ggdb
	GCC_FLAGS =
else
	GCC_VER = $(shell gcc -dumpversion | cut -d . -f 1)
	ifeq ($(shell if [ $(GCC_VER) -ge 4 ]; then echo 1; else echo 0; fi), 1)
		GCC_FLAGS = -fvisibility=hidden -fvisibility-inlines-hidden
	else
		GCC_FLAGS =
	endif
	OPTIM_FLAGS = -O2
	DEBUG = 0
endif
ifeq ($(strip $(NOGL)), 1)
	O_GL =
	PKG_GL =
	CFLAGS_GL = -D__NO_OPEN_GL__
else
	O_GL = GTKGL.o GLBase.o GTKGLWindow.o GTKFont.o GTKGLDrawingArea.o
	PKG_GL = gtkglext-1.0
	CFLAGS_GL = 
endif
CC = $(GCC) $(GCC_FLAGS)
PKG_CONFIG = gtk+-2.0 pango $(PKG_GL)
EXTRA_CFLAGS = $(shell pkg-config --cflags $(PKG_CONFIG)) $(CFLAGS_GL)
CFLAGS = -c $(OPTIM_FLAGS) -D__GTKpp_EXPORT__ -I./include/ -I./ $(EXTRA_CFLAGS) -o $*.o
LIBS = $(shell pkg-config --libs $(PKG_CONFIG))
LFLAGS = $(OPTIM_FLAGS) -shared $(O) $(LIBS) -Wl,-soname,$(SO_out) -o $(SO)
AR = ar cr
RANLIB = ranlib
STRIP = strip -x

O = GTK.o GTKWidget.o GTKWindow.o GTKFrame.o GTKDialog.o GTKFileDialog.o GTKMessageBox.o GDKPixbuf.o GTKBox.o GTKHBox.o GTKVBox.o GTKKey.o GTKFixed.o GTKButton.o GTKEntry.o GTKImage.o GTKLabel.o GTKHUpDown.o GTKContainer.o GTKEvents.o GTKScrolledWindow.o GTKTextBuffer.o GTKTextView.o GTKList.o GTKCheckBox.o GTKComboBox.o GTKColourSelectionDialog.o GTKAboutDialog.o GTKDrawingArea.o GTKMenu.o GTKMenuBar.o GTKMenuItem.o GTKMenuShell.o GTKProgressBar.o GTKRange.o GTKScale.o GTKHScale.o GTKVScale.o GTKSeparator.o GTKHSeparator.o GTKVSeparator.o $(O_GL)
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
	if [ $(DEBUG) -eq 0 ]; then $(STRIP) $(SO); fi

.cpp.o:
	$(CC) $(CFLAGS) $*.cpp

clean: clean-recursive
	rm -f *.o *~

clean-recursive:
	@cd include && $(MAKE) clean
	@cd bin && $(MAKE) clean

# GLPixelFormats.o: GLPixelFormats.cpp # for Windows only!
# GTKAdjustment.o: GTKAdjustment.cpp # not yet, not ready yet.
# GTKViewport.o: GTKViewport.cpp # not yet, not ready yet.
