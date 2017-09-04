all: server daemon

server: src/server.c
	gcc -Wall -Iinclude src/server.c src/json.c -o bin/server.out -Llib -l:libjsmn.a -lmicrohttpd

daemon: usb
	./bin/usbDaemon

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

# INICIO - PRUEBA DE daemonTest
# daemonTest: daemonTest.o usbPostListaDisp.o usb.o jsonUSB.o 
# 	gcc -Wall -pthread obj/usb.o obj/daemonTest.o obj/usbPostListaDisp.o obj/jsonUSB.o -o bin/daemonTest -ludev -ljson

# usb.o: src/usb/usb.c
# 	gcc -c -Wall  -Iinclude/ src/usb/usb.c -o obj/usb.o -ludev

# jsonUSB.o: src/usb/jsonUSB.c include/usbFunctions.h
# 	gcc -c -Wall -Iinclude/ src/usb/jsonUSB.c -o obj/jsonUSB.o -ljson

# usbPostListaDisp.o: src/usb/usbPostListaDisp.c include/usbFunctions.h
# 	gcc -c -Wall -Iinclude/ src/usb/usbPostListaDisp.c -o obj/usbPostListaDisp.o

# daemonTest.o: src/usb/daemonTest.c include/usbFunctions.h
# 	gcc -c -Wall -Iinclude/ src/usb/daemonTest.c -o obj/daemonTest.o -ludev


usb: usbController.o usbDaemon.o usbFunctions.o usbLista.o usbJson.o
	gcc -Wall obj/usb/*.o -o bin/usbDaemon -ludev -ljson

usbDaemon.o: src/usb/usbDaemon.c include/usb/*.h
	gcc -c -Wall -Iinclude/usb/ src/usb/usbDaemon.c -o obj/usb/usbDaemon.o

usbController.o: src/usb/usbController.c
	gcc -c -Wall -Iinclude/usb/ src/usb/usbController.c -o obj/usb/usbController.o -ludev

usbFunctions.o: src/usb/usbFunctions.c
	gcc -c -Wall -Iinclude/usb/	src/usb/usbFunctions.c -o obj/usb/usbFunctions.o

usbLista.o: src/usb/usbLista.c
	gcc -c -Wall -Iinclude/usb/ src/usb/usbLista.c -o obj/usb/usbLista.o

usbJson.o: src/usb/usbJson.c
	gcc -c -Wall -Iinclude/usb/ src/usb/usbJson.c -o obj/usb/usbJson.o -ljson


# FIN - PRUEBA DE daemonTest

# INICIO - PRUEBA USBSOCKET

# clientUSB: 
# 	gcc -Wall src/usb/pruebaCliente.c -o bin/cliente

# FIN - USB SOCKET
clean:
	rm -rf obj/*.o bin/server lib/*.so obj/*.o web_server/bootstrap.min.* web_server/jquery.min.* web_server/vue.* web_server/bootstrap.min.* web_server/materialize.min* web_server/fonts

mount:
	/bin/bash scripts/mount.sh

umount:
	umount /dev/loop0
	umount /dev/loop1

.PHONY: install clean kill
