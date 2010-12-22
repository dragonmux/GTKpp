PACKAGES=`pkg-config --cflags gtk+-2.0 pango gtkglext-1.0`
sed -e "s:@PACKAGES@:${PACKAGES}:g" libGTK++.pc.in > libGTK++.pc
