import os
import json
from flask import Flask
import firebase_admin
from firebase_admin import credentials, db

app = Flask(__name__)

firebase_key = json.loads(os.environ['FIREBASE_KEY'])
cred = credentials.Certificate(firebase_key)

firebase_admin.initialize_app(
    cred, {
        'databaseURL':
        'https://hydroponicsai-default-rtdb.asia-southeast1.firebasedatabase.app'
    })

SENSOR_THRESHOLDS = {
    "moisture": {
        "LB": 30,
        "UB": 80
    },
    "temperature": {
        "LB": 18,
        "UB": 35
    },
    "ph": {
        "LB": 5.5,
        "UB": 7.5
    },
    "humidity": {
        "LB": 30,
        "UB": 70
    },
    "nitrogen (mg/Kg)": {
        "LB": 10,
        "UB": 50
    },
    "phosphorous (mg/Kg)": {
        "LB": 10,
        "UB": 50
    },
    "potassium (mg/Kg)": {
        "LB": 10,
        "UB": 50
    }
}


def generate_control_signals(data):
    control = {}
    for sensor, limits in SENSOR_THRESHOLDS.items():
        if sensor in data:
            value = data[sensor]
            if isinstance(value, (int, float)):
                if value < limits["LB"]:
                    control[f"{sensor}_Control"] = "LOW"
                    control[
                        f"message_{sensor}"] = f"{sensor} LOW. Take action."
                elif value > limits["UB"]:
                    control[f"{sensor}_Control"] = "HIGH"
                    control[
                        f"message_{sensor}"] = f"{sensor} HIGH. Take action."
                else:
                    control[f"{sensor}_Control"] = "NORMAL"
                    control[f"message_{sensor}"] = f"{sensor} within range."
    return control


@app.route("/")
def control_logic():
    try:
        data = db.reference("/hydroponics/latest").get()
        print("Sensor Data:", data)

        if not isinstance(data, dict):
            return "No valid sensor data found", 400

        control = generate_control_signals(data)
        db.reference("/hydroponics/control").set(control)

        return f"Control updated: {control}", 200

    except Exception as e:
        return f"Error: {str(e)}", 500


@app.route("/ping")
def ping():
    print("Ping received from UptimeRobot!")
    return "Server is alive", 200


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=81)
