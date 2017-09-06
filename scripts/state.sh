PUERTO_SOCKET_DAEMON=8238
if [ $(pgrep  -f usbDaemon) ]; then
	PID_NAME=$(pgrep  -f usbDaemon)
	# kill $PID_NAME
	echo "Proceso daemon ya esta corriendo con el ${PID_NAME}"
	# fuser -k 8237/tcp
	echo "Puede matar al daemon usando:  make kill"
else
	echo "Daemon iniciado"
	./bin/usbDaemon
fi
