LN = ln -sfT
LIBDIR = /usr/lib/
PKGDIR = /usr/lib/pkgconfig/

SO = libGTK++.so
A = libGTK++.a
LA = libGTK++.la
PC = libGTK++.pc
IN = libGTK++.pc.in

clean:
	rm -f *.so* *.a* *~

install:
	cp $(SO) $(LIBDIR)
	cp $(LA) $(LIBDIR)
	cp $(A) $(LIBDIR)
	rm -f libGTK++.pc
	$(SHELL) ./libGTK++.pc.sh
	cp $(PC) $(PKGDIR)
	chown root $(PKGDIR)$(PC)
	chgrp root $(PKGDIR)$(PC)
	chmod +r $(LIBDIR)$(LA)
