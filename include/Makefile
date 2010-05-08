INCDIR = /usr/include/GTK++/

clean:
	rm -f *~

install:
	if [ ! -d $(INCDIR) ]; then \
		mkdir $(INCDIR); \
	fi
	rm -f $(INCDIR)*.h
	cp GTK++.h $(INCDIR)
	chmod +r $(INCDIR)GTK++.h
	cp GTK++_Compat.h $(INCDIR)
	chmod +r $(INCDIR)GTK++_Compat.h
