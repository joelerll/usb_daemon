<!-- errores ortograficos -->
# Descripcion del proyecto
Lee los puertos usb. Se puede listar los dispositivos conectados, nombrar un dispositivo, editar un archivo del dispositivo y leer un archivo del dispositivo

# 5 Simples pasos

```sh
> sudo make install                 # instala las dependencias
> make                              # complila los archivos
> make daemon                       # ejecuta el daemon
> ./bin/server 5555                 # ejecutar el servidor
> ./client 5555 listar_dispositivos # usar el cliente
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

# Desarrolladores

* Joel Rodriguez
* Bosco Andrade
* Israel Cano

# Dependencias

Direccion url de las dependencias y para que las usamos
