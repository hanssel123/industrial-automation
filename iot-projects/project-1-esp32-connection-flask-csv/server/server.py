from flask import Flask, request

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    data = request.data.decode("utf-8")
    with open('/home/hanssel/Documents/Automatica_3/Proyecto_1_esp_python_csv/server/data.csv', 'a') as f:
        f.write(data + '/n')

    return 'Datos recibidos', 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)