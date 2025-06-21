
import os
import json
from flask import Flask
import firebase_admin
from firebase_admin import credentials, db

app = Flask(__name__)

firebase_key = json.loads(os.environ['FIREBASE_KEY'])  # Set in .env as a stringified JSON
cred = credentials.Certificate(firebase_key)

firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://hydroponicsai-default-rtdb.asia-southeast1.firebasedatabase.app'
})

@app.route("/")
def control_logic():
    try:
        data = db.reference("/hydroponics/latest").get() #read latest sensor values from the database
        print("Sensor Data:", data)

        control = {}

        
        if isinstance(data, dict) and 'moisture' in data:#for example we have taken moisture control logic
            if data['moisture'] > 30:
                control['waterPump'] = True
                control['message'] = "Moisture low. Pump ON Test"
            else:
                control['waterPump'] = False
                control['message'] = "Moisture normal. Pump OFF"

            db.reference("/hydroponics/control").set(control)
            return f"Control updated: {control}", 200
        else:
            return "No valid sensor data found", 400

    except Exception as e:
        return f"Error: {str(e)}", 500

@app.route("/ping")
def ping():
    return "Server is alive", 200

#Run the Flask server
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=81)
