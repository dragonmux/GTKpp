# This file is part of GTK++ (libGTK++)
# Copyright © 2012 Richard/Rachel Mant (dx-mon@users.sourceforge.net)
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

LIBDIR ?= /usr/lib
PKGDIR = $(LIBDIR)/pkgconfig
INSTALL = install
INSTALL_FILE = $(INSTALL) -m644

SO = libGTK++.so
A = libGTK++.a
PC = libGTK++.pc
IN = libGTK++.pc.in

clean:
	$(call run-cmd,rm,GTK+/bin,$(SO) $(A))

install:
	$(call run-cmd,install_file,$(SO),$(LIBDIR))
	$(call run-cmd,install_file,$(A),$(LIBDIR))
	$(call run-cmd,rm,$(PC),$(PC))
	$(Q)$(SHELL) ./libGTK++.pc.sh
	$(Q)sed -i -e 's:@LIBDIR@:$(LIBDIR):g' libGTK++.pc
	$(call run-cmd,install_file,$(PC),$(PKGDIR))
	$(Q)ldconfig
