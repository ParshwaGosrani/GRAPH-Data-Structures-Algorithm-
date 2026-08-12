from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess
import os

app = Flask(__name__)
CORS(app) # Allows your HTML file to fetch data from this server

@app.route('/get-route')
def get_route():
    src = request.args.get('src')
    dest = request.args.get('dest')
    
    # Determine the compiled C executable name based on OS (Windows vs Mac)
    exe_name = 'smart_city.exe' if os.name == 'nt' else './smart_city'
    
    try:
        # Run the C program in Web API mode!
        result = subprocess.run([exe_name, 'route', str(src), str(dest)], capture_output=True, text=True)
        return jsonify({"status": "success", "raw_output": result.stdout.strip()})
    except Exception as e:
        return jsonify({"status": "error", "message": "Failed to run C program. Did you compile it?"})

if __name__ == '__main__':
    print("🚀 Smart City Server running on http://127.0.0.1:5000")
    app.run(port=5000)