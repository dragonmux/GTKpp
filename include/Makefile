INCDIR = /usr/include/GTK++
INSTALL = install -m644

clean:
	rm -f *~

install:
	install -m755 -d $(INCDIR)
	rm -f $(INCDIR)/*.h
	$(INSTALL) GTK++.h $(INCDIR)
	$(INSTALL) GTK++_Compat.h $(INCDIR)
