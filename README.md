# Descripcion del proyecto
Lee los puertos usb. Se puede listar los dispositivos conectados, nombrar un dispositivo, editar un archivo del dispositivo y leer un archivo del dispositivo

# Instrucciones de instalacion

### Pasos
```sh
> sudo make install
> make
> source .virtualenv/bin/activate
```

Correr el servidor, daemon usb, luego el cliente en python
(como hacer que el servidor y el daemon usb corrar en background al hacer make?)

### Correr el cliente web

1. Tiene que estar activado el virtualenv
```sh
> source .virtualenv/bin/activate
```

2. Ejecutar
```sh
> make client
```

3. Se abrira el navegador por defecto en el puerto 5000

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
