from flask import Flask, request

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_file():
    data = request.data.decode("utf-8")
    with open('C:/Users/hanssel/Documents/repos_final/industrial4/industrial-automation/iot-projects/project-1-esp32-connection-flask-csv/server/data.csv', 'a') as f:
        f.write(data + '/n')

    return 'Datos recibidos', 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)