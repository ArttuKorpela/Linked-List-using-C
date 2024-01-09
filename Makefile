HT: HTTavoitetaso.o HTPerusKirjasto.o HTTavoiteKirjasto.o
	gcc HTTavoitetaso.o HTPerusKirjasto.o HTTavoiteKirjasto.o -o HT
HTTavoite.o: HTTavoitetaso.c HTPerusKirjasto.h
	gcc HTTavoitetaso.c -c -std=c99 -Wall -pedantic
HTPerusKirjasto.o: HTPerusKirjasto.c HTPerusKirjasto.h
	gcc HTPerusKirjasto.c -c -std=c99 -Wall -pedantic
HTTavoiteKirjasto.o: HTTavoiteKirjasto.c HTPerusKirjasto.h
	gcc HTTavoiteKirjasto.c -c -std=c99 -Wall -pedantic