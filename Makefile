all: todo

todo: main.o
	gcc -Wall obj/main.o -o bin/server -Llib -l:libjsmn.a -lmicrohttpd

main.o: src/main.c
	gcc -Iinclude -c -Wall src/main.c -o obj/main.o

install:
	/bin/bash setup.sh

ejecutar:
	echo "Ejecutara el server y el .py client"

clean:
	rm -f obj/*.o bin/server lib/*.so obj/*.o

mount:
	/bin/bash mount.sh

umount:
	umount /dev/loop0
	umount /dev/loop1

.PHONY: install clean
