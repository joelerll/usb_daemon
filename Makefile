all: server daemon

server: src/server.c
	gcc -Wall -Iinclude src/server.c src/solicitudes_server.c -o bin/server -Llib -ljson  -lmicrohttpd 

daemon: usb
	@/bin/bash scripts/state.sh

clientTest: clientTestUsb
	./bin/cliente

kill:
	@#mata el proceso del deamon
	@/bin/bash scripts/kill.sh

install:
	@/bin/bash scripts/setup.sh

main.o: src/main.c
	gcc -Iinclude -c -Wall src/main.c -o obj/main.o

# json: src/test/json.test.c
# 	gcc -Iinclude -Wall src/test/json.test.c -o bin/json.out -Llib -l:libjsmn.a

# server_test: src/test/server.test.c
# 	gcc -Wall src/test/server.test.c -o bin/server.out -Llib -l:libjsmn.a -lmicrohttpd

client:
	/bin/bash scripts/client.sh
	# source .virtualenv/bin/activate
	python3 server.py

usb: usbController.o usbDaemon.o usbFunctions.o usbLista.o usbJson.o usbServer.o
	@gcc -Wall obj/usb/*.o -o bin/usbDaemon -ludev -ljson -pthread

usbDaemon.o: src/usb/usbDaemon.c include/usb/*.h
	@gcc -c -Wall -Iinclude/usb/ src/usb/usbDaemon.c -o obj/usb/usbDaemon.o

usbController.o: src/usb/usbController.c
	@gcc -c -Wall -Iinclude/usb/ src/usb/usbController.c -o obj/usb/usbController.o -ludev

usbFunctions.o: src/usb/usbFunctions.c
	@gcc -c -Wall -Iinclude/usb/	src/usb/usbFunctions.c -o obj/usb/usbFunctions.o

usbLista.o: src/usb/usbLista.c
	@gcc -c -Wall -Iinclude/usb/ src/usb/usbLista.c -o obj/usb/usbLista.o

usbJson.o: src/usb/usbJson.c
	@gcc -c -Wall -Iinclude/usb/ src/usb/usbJson.c -o obj/usb/usbJson.o -ljson

usbServer.o: src/usb/usbServer.c
	@gcc -c -Wall -Iinclude/usb/ src/usb/usbServer.c -o obj/usb/usbServer.o -ljson

clientTestUsb: 
	gcc -Wall src/usb/cliente.c -o bin/cliente -ljson

# FIN - USB SOCKET
clean:
	rm -rf obj/*.o bin/server bin/usbDaemon bin/jsonPrueba bin/server.out bin/cliente lib/*.so obj/*.o web_server/bootstrap.min.* web_server/jquery.min.* web_server/vue.* web_server/bootstrap.min.* web_server/materialize.min* web_server/fonts obj/usb/*.o

mount:
	/bin/bash scripts/mount.sh

umount:
	umount /dev/loop0
	umount /dev/loop1

.PHONY: install clean kill
