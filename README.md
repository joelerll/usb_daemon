<!-- errores ortograficos -->
# Descripción del proyecto
Lee los puertos usb. Se puede listar los dispositivos conectados, nombrar un dispositivo, editar un archivo del dispositivo y leer un archivo del dispositivo

# 5 Simples pasos

```sh
> sudo make install                 # instala las dependencias
> make                              # complila los archivos
> make daemon                       # ejecuta el daemon
> ./bin/server 5555                 # ejecutar el servidor
> ./client 5555 listar_dispositivos # usar el cliente
```

<blockquote class="imgur-embed-pub" lang="en" data-id="e2jq62S"><a href="//imgur.com/e2jq62S">View post on imgur.com</a></blockquote><script async src="//s.imgur.com/min/embed.js" charset="utf-8"></script>

# Uso cliente

```sh
> ./client --help

```

# Matar al daemon
Es muy fácil, solo ejecutar

```sh
> make kill
```

# Desarrolladores

* Joel Rodriguez
* Bosco Andrade
* Israel Cano

# Dependencias

## Dependencias C

* libmicrohttpd
* libudev
* libjson

## Dependencias cliente

* python3
* requests
* tabulate