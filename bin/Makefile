LN = ln -sfT
LIBDIR ?= /usr/lib
PKGDIR = $(LIBDIR)/pkgconfig
INSTALL = install -m644

SO = libGTK++.so
A = libGTK++.a
PC = libGTK++.pc
IN = libGTK++.pc.in

clean:
	rm -f *.so* *.a* *~

install:
	$(INSTALL) $(SO) $(LIBDIR)
	$(INSTALL) $(A) $(LIBDIR)
	rm -f libGTK++.pc
	$(SHELL) ./libGTK++.pc.sh
	sed -i -e 's:@LIBDIR@:$(LIBDIR):g' libGTK++.pc
	$(INSTALL) $(PC) $(PKGDIR)
	ldconfig
