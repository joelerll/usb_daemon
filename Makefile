all: todo
## daemon build. json build

todo:
	echo "ejecutar el daemon, y el server aqui mismo, mandar un mensaje de como ejecutar el comando y ayuda del cliente"
	@echo "Por favor ejecutar el archivo cliente"
	@echo " "
	python3 client.py --help

server: server_build
	./bin/server.out
	## nohup, & disown

daemon: daemonTest
	./bin/daemonTest
	# verifica si el daemon se esta ejecutando
	# @PID_INIT=$(./bin/daemonTest 2>&1)
	# @echo -e -n $PID_INIT > pid_file 

kill:
	@#mata el proceso del deamon
	@/bin/bash kill.sh

# todo: main.o
# 	gcc -Wall obj/main.o -o bin/server -Llib -l:libjsmn.a -lmicrohttpd

main.o: src/main.c
	gcc -Iinclude -c -Wall src/main.c -o obj/main.o

json: src/test/json.test.c
	gcc -Iinclude -Wall src/test/json.test.c -o bin/json.out -Llib -l:libjsmn.a

server_build: src/server.c
	gcc -Wall -Iinclude src/server.c src/json.c -o bin/server.out -Llib -l:libjsmn.a -lmicrohttpd

server_test: src/test/server.test.c
	gcc -Wall src/test/server.test.c -o bin/server.out -Llib -l:libjsmn.a -lmicrohttpd

install:
	/bin/bash setup.sh

client:
	/bin/bash client.sh
	# source .virtualenv/bin/activate
	python3 server.py

# INICIO - PRUEBA DE daemonTest
daemonTest: daemonTest.o usbPostListaDisp.o usb.o jsonUSB.o 
	gcc -Wall -pthread obj/usb.o obj/daemonTest.o obj/usbPostListaDisp.o obj/jsonUSB.o -o bin/daemonTest -ludev -ljson

usb.o: src/usb/usb.c
	gcc -c -Wall  -Iinclude/ src/usb/usb.c -o obj/usb.o -ludev

jsonUSB.o: src/usb/jsonUSB.c include/usbFunctions.h
	gcc -c -Wall -Iinclude/ src/usb/jsonUSB.c -o obj/jsonUSB.o -ljson

usbPostListaDisp.o: src/usb/usbPostListaDisp.c include/usbFunctions.h
	gcc -c -Wall -Iinclude/ src/usb/usbPostListaDisp.c -o obj/usbPostListaDisp.o

daemonTest.o: src/usb/daemonTest.c include/usbFunctions.h
	gcc -c -Wall -Iinclude/ src/usb/daemonTest.c -o obj/daemonTest.o -ludev



# FIN - PRUEBA DE daemonTest

# INICIO - PRUEBA USBSOCKET

clientUSB: 
	gcc -Wall src/usb/pruebaCliente.c -o bin/cliente

# FIN - USB SOCKET
clean:
	rm -rf obj/*.o bin/server lib/*.so obj/*.o web_server/bootstrap.min.* web_server/jquery.min.* web_server/vue.* web_server/bootstrap.min.* web_server/materialize.min* web_server/fonts

mount:
	/bin/bash mount.sh

umount:
	umount /dev/loop0
	umount /dev/loop1

.PHONY: install clean kill
