# cambiar a binrio a daemon.out
# if [ ! -e pid_file ]; then
#     echo "> Archivo pid_file no existe"	
# else
# 	PID=$(<pid_file)
# 	$PID_NAME = pgrep  -f server.out
# 	echo "> Tratando de terminado proceso ${PID}"
# 	# ps -p $PID
# 	if [ -d "/proc/${PID}" ]; then
# 		kill $PID
# 	else
# 		echo "> El proceso no existe"
# 		rm -f pid_file
# 		echo "> Borrando el archivo pid_file"
# 		echo "> Parece que el archivo tenia un pid que no existe, por favor vuelva a correr el daemon"
# 		echo ""
# 		echo -e "por favor ejecute \033[92mmake daemon\033[0m"
# 		echo ""
# 	fi
# fi

if [ $(pgrep  -f daemonTest) ]; then
	PID_NAME=$(pgrep  -f daemonTest)
	kill $PID_NAME
	echo "Proceso daemon terminado"
else
	echo "> El proceso no existe"
	echo "> Parece que el archivo tenia un pid que no existe, por favor vuelva a correr el daemon"
	echo ""
	echo -e "por favor ejecute \033[92mmake daemon\033[0m"
	echo ""
fi
