import json
from flask import Flask
from flask import request, send_from_directory,make_response,jsonify,request
import os
import requests as r
import random, threading, webbrowser

url = "http://127.0.0.1:5000"
# port = 5000 + random.randint(0, 999)
# root_dir = os.path.dirname(os.getcwd())

app = Flask(__name__,static_folder='web_server',static_url_path='')

@app.route('/api/listar_dispositivos', methods=['GET'])
def listar_dispositivos():
    res = r.get("http://localhost:8888/listar_dispositivos", data=None)
    return res.text

@app.route('/api/nombrar_dispositivo', methods=['POST'])
def nombrar_dispositivo():
    res = r.post("http://localhost:8888/nombrar_dispositivo", data={"nombrar_dispositivo": "{'nodo': '/dev/sdb1', 'nombre': 'nuevo_nombre','solicitud': 'nombrar_dispositivo'}"})
    return res.text

@app.route('/api/leer_archivo', methods=['POST'])
def leer_archivo():
    res = r.post("http://localhost:8888/leer_archivo", data={"leer_archivo": "{'nombre_archivo': 'archivo', 'nombre': 'nombre?','solicitud': 'leer_archivo'}"})
    return res.text

@app.route('/api/escribir_archivo', methods=['POST'])
def escribir_archivo():
    res = r.post("http://localhost:8888/escribir_archivo", data={"escribir_archivo": "{'nombre': 'nodo_nombre', 'nombre_archivo': 'archvivo','solicitud': 'escribir_archivo', 'tamano_contenido': 5, 'contenido': 'contenido id'}"})
    return res.text

@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({'error': 'Not found'}), 404)

@app.route('/', methods=['GET'])
def index():
	return send_from_directory('web_server', 'index.html')

if __name__ == '__main__':
    # threading.Timer(1.25, lambda: webbrowser.open(url)).start()
    app.run(port=5000, debug=True) #debug=False
