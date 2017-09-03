<!-- errores ortograficos -->
# Descripcion del proyecto
Lee los puertos usb. Se puede listar los dispositivos conectados, nombrar un dispositivo, editar un archivo del dispositivo y leer un archivo del dispositivo

# 5 Simples pasos

```sh
> sudo make install 				# instala las dependencias
> make 								# complila los archivos
> make daemon						# ejecuta el daemon
> ./bin/server 5555 				# ejecutar el servidor
> ./client 5555 listar_dispositivos # usar el cliente
```

# Instalacion
La siguente instruccion instalara las dependencias necesarias para el proyecto

```sh
> sudo make install
```

# Uso cliente
<!-- mostrar gif del uso del cliente los resultados -->

```sh
> ./client --help

```

# Matar al daemon
Es muy facil, solo ejecutar

```sh
> make kill
```

### Correr el cliente web

1. Ejecutar
```sh
> make client
```

2. Se abrira el navegador por defecto en el puerto 5000

#### Montar el virtual_usb y virtual_usb_2

```sh
> sudo make mount
```

Para comprobar que se ha montado correctamente ejecutar:

```sh
> df -h
```
Estara montado en /media/usb_virtual u /media/usb_virtual_2

Aqui podram crear archivos y seran compartidos a todos


__Para desmontarlo__

```sh
> sudo make umount
```

# Dependencias

Direccion url de las dependencias y para que las usamos
