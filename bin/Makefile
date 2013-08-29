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
include ../Makefile.inc

LIBDIR ?= $(PREFIX)/lib
PKGDIR = $(LIBDIR)/pkgconfig
INSTALL = install
INSTALL_FILE = $(INSTALL) -m644
INSTALL_DIR = $(INSTALL) -m755 -d

PACKAGES = $(strip $(shell pkg-config --cflags gtk+-2.0 pango gtkglext-1.0))
SED = sed -e 's:@PACKAGES@:$(PACKAGES):g' -e 's:@LIBDIR@:$(LIBDIR):g' -e 's:@PREFIX@:$(PREFIX):g'

SO = libGTK++.so
A = libGTK++.a
PC = libGTK++.pc
IN = libGTK++.pc.in

quiet_cmd_sed = " GEN   $(3)"
cmd_sed = $(SED) $(2) > $(3)

clean:
	$(call run-cmd,rm,GTK+/bin,$(SO) $(A))

$(LIBDIR):
	$(call run-cmd,install_dir,$(LIBDIR))

$(PKGDIR):
	$(call run-cmd,install_dir,$(PKGDIR))

install: $(LIBDIR) $(PKGDIR)
	$(call run-cmd,install_file,$(SO),$(LIBDIR))
	$(call run-cmd,install_file,$(A),$(LIBDIR))
	$(call run-cmd,rm,$(PC),$(PC))
	$(call run-cmd,sed,$(IN),$(PC))
	$(call run-cmd,install_file,$(PC),$(PKGDIR))
	$(call ldconfig)
