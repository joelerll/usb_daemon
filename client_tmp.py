#!/usr/bin/python3.5
"""
Errores:
calcular que el tamano de contenido que se envia sea el correcto
"""

"""
GET
/listar_dispositivo

*response
{
    solicitud: 'listar_dispositivos',
    dispositivos: [{
        nombre: '',
        id: 'vendor:device',
        montaje: '/home',
        nodo: '/dev/'
    }],
    status: 0,
    str_error: ''
}
"""

"""
POST
/nombrar_dispositivo

*request
{
    solicitud: 'nombrar_dispositivo',
    nodo: '/dev',
    nombre: ''
}

*response
{
    solicitud: 'nombrar_dispositivo',
    nombre: '',
    nodo: '/dev/'
    status: 0,
    str_error: ''
    status: 0,
}
"""

"""
GET
/leer_archivo

*request
{
    solicitud: 'leer_archivo',
    nombre: '',
    nombre_archivo: ''
}

*response
{
    solicitud: 'leer_archivo',
    nombre: '',
    nombre_archivo: '',
    contenido: ''
    status: 0,
    str_error: ''
}
"""

"""
POST
/escribir_archivo

*request
{
    solicitud: 'escribir_archivo',
    nombre: '',
    nombre_archivo: '',
    tamano_contenido: '',
    contenido: ''
}

*response
{
    solicitud: 'escribir_archivo',
    nombre: '',
    nombre_archivo: '',
    status: 0,
    str_error: ''
}
"""

menu = """
    (1) listar_dispositivo
    (2) nombrar_dispositivo
    (3) leer_archivo
    (4) escribir_archivo
"""
import requests
print(menu)
opcion = input("Ingrese el numero de la opcion ")
##http://urwid.org/
if (opcion == '1'):
    r = requests.get("http://localhost:8888/listar_dispositivos", data=None)
    print(r.text)

if (opcion == '2'):
    r = requests.post("http://localhost:8888/nombrar_dispositivo", data={"nombrar_dispositivo": "{'nodo': '/dev/sdb1', 'nombre': 'nuevo_nombre','solicitud': 'nombrar_dispositivo'}"})
    print(r.text)

if (opcion == '3'):
    r = requests.post("http://localhost:8888/leer_archivo", data={"leer_archivo": "{'nombre_archivo': 'archivo', 'nombre': 'nombre?','solicitud': 'leer_archivo'}"})
    print(r.text)

if (opcion == '4'):
    r = requests.post("http://localhost:8888/escribir_archivo", data={"escribir_archivo": "{'nombre': 'nodo_nombre', 'nombre_archivo': 'archvivo','solicitud': 'escribir_archivo', 'tamano_contenido': 5, 'contenido': 'contenido id'}"})
    print(r.text)

