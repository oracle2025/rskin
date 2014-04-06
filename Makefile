rskin: rskin.o skin.o ani_button.o skincanvas.o Makefile
	gcc skin.o skincanvas.o rskin.o ani_button.o `wx-config --libs` -o rskin

clean:
	rm rskin *.o

rskin.o: rskin.cpp rskin.h Makefile
	gcc -c rskin.cpp `wx-config --cflags`

skin.o: skin.cpp skin.h Makefile
	gcc -c skin.cpp `wx-config --cflags`

skincanvas.o: skincanvas.cpp skincanvas.h Makefile
	gcc -c skincanvas.cpp `wx-config --cflags`

ani_button.o: ani_button.cpp ani_button.h Makefile
	gcc -c ani_button.cpp `wx-config --cflags`
