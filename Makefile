all: server daemon

server: src/server.c
	gcc -Wall -Iinclude src/server.c src/json.c -o bin/server.out -Llib -l:libjsmn.a -lmicrohttpd

daemon: testDaemon
	./bin/daemonTest

kill:
	@#mata el proceso del deamon
	@/bin/bash scripts/kill.sh

install:
	@/bin/bash scripts/setup.sh

main.o: src/main.c
	gcc -Iinclude -c -Wall src/main.c -o obj/main.o

json: src/test/json.test.c
	gcc -Iinclude -Wall src/test/json.test.c -o bin/json.out -Llib -l:libjsmn.a

server_test: src/test/server.test.c
	gcc -Wall src/test/server.test.c -o bin/server.out -Llib -l:libjsmn.a -lmicrohttpd

client:
	/bin/bash scripts/client.sh
	# source .virtualenv/bin/activate
	python3 server.py
# INICIO - PRUEBA DE DAEMON
testDaemon: daemon.o usb.o 
	gcc obj/usb.o obj/daemon.o -o bin/daemonTest -ludev

usb.o: src/usb/usb.c
	gcc -c -Wall  -Iinclude/ src/usb/usb.c -o obj/usb.o -ludev

daemon.o: src/usb/daemon.c include/usbFunctions.h
	gcc -c -Wall -Iinclude/ src/usb/daemon.c -o obj/daemon.o -ludev
# FIN - PRUEBA DE DAEMON

clean:
	rm -rf obj/*.o bin/server lib/*.so obj/*.o web_server/bootstrap.min.* web_server/jquery.min.* web_server/vue.* web_server/bootstrap.min.* web_server/materialize.min* web_server/fonts

mount:
	/bin/bash scripts/mount.sh

umount:
	umount /dev/loop0
	umount /dev/loop1

.PHONY: install clean kill
