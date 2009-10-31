PACKAGES=`pkg-config --cflags gtk+-2.0 pango gtkglext-1.0`
echo ":t" > subs.sed
echo "s,@PACKAGES@,$PACKAGES,;t t" >> subs.sed
sed -f subs.sed libGTK++.pc.in > libGTK++.pc
rm subs.sed
