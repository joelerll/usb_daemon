# Descripcion del proyecto
Lee los puertos usb. Se puede listar los dispositivos conectados, nombrar un dispositivo, editar un archivo del dispositivo y leer un archivo del dispositivo

# Instrucciones de instalacion

### Pasos
```sh
> sudo make install
> make
```

Correr el servidor, daemon usb, luego el cliente en python
(como hacer que el servidor y el daemon usb corrar en background al hacer make?)

### Ejecutar el servidor

1.

```sh
> make server
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


# Instrucciones de uso servidor y cliente

imagenes gif de uso

# Test archivos

usar el virtual_usb para los test
