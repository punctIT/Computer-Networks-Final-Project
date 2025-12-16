import socket
import json
import time
import psutil 
import struct
import os

SERVER_IP = '127.0.0.1'
SERVER_PORT = 9000
HOSTNAME = socket.gethostname()

def get_metrics():
    return {
        "hostname": HOSTNAME,
        "ip_address": socket.gethostbyname(HOSTNAME),
        "os_info": os.name, 
        "cpu_load": psutil.cpu_percent(interval=None),
        "ram_usage": psutil.virtual_memory().percent,
        "disk_usage": psutil.disk_usage('/').percent,
        "status_message": "OK",
        "active_user": psutil.users()[0].name if psutil.users() else "system"
    }

def send_data():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((SERVER_IP, SERVER_PORT))
        while True:
            try:
                data = get_metrics()
                json_str = json.dumps(data)
                payload = json_str.encode('utf-8')
                header = struct.pack('I', len(payload)) 
                
                packet = header + payload
                s.sendall(packet)
                print(f"Trimis date de la {HOSTNAME}: CPU {data['cpu_load']}%")

            except Exception as e:
                print(f"Eroare conexiune: {e}")
            time.sleep(5)

if __name__ == "__main__":
    print(f"Pornire Agent pe {HOSTNAME}...")
    send_data()