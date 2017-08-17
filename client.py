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
}
"""

import requests
headers = {'Content-type': 'application/json', 'Accept': 'text/plain','Content-Length': '56'}
r = requests.post("http://localhost:8888", data={"datos": "{'nodo': '/dev/sdb1', 'nombre': 'nombre?','nombrar_dispositivo': 'mi_nuevo_nombre'}"})
# r = requests.get("http://localhost:8888/listar_dispositivos")
print(r.headers)
print(r.request.headers)
print(r.status_code, r.reason)
print(r.text)
# from urllib.parse import urlencode
# from urllib.request import Request, urlopen
#
# url = 'http://localhost:8888' # Set destination URL here
# post_fields = {'nombrar_dispositivo': 'mi_nuevo_nombre', 'nodo': '/dev/sdb1', 'nombre': 'nombre?'}     # Set POST fields here
#
# request = Request(url, urlencode(post_fields).encode())
# json = urlopen(request).read().decode()
# print(json)
#
# import http.client
# import json
# connection = http.client.HTTPConnection('http://localhost:8888')
# headers ={'nombrar_dispositivo': 'mi_nuevo_nombre', 'nodo': '/dev/sdb1', 'nombre': 'nombre?'}
# foo = {'text': 'hello'}
# json_foo = json.dumps(foo)
# connection.request('POST', '/', json_foo, headers)
#
# response = connection.getresponse()
# print(response.read())
# h2.request('POST', '/', body=None , headers={}, encode_chunked=False)

# import pip
# installed_packages = pip.get_installed_distributions()
# installed_packages_list = sorted(["%s==%s" % (i.key, i.version)
#      for i in installed_packages])
# print(installed_packages_list)
# sorted(["%s==%s" % (i.key, i.version) for i in pip.get_installed_distributions()])
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
