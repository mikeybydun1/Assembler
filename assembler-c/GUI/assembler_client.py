import socket
import pickle
from encrypt_decrypt import encrypt_data


class AssemblyClient:
    def __init__(self, host="localhost", port=5000):
        self.host = host
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))

    def send_file(self, file_name, file_content):
        data = {
            "file_name": file_name,
            "file_content": file_content
        }

        # Serialize and encrypt the data
        encrypted_data = encrypt_data(pickle.dumps(data))

        self.socket.sendall(encrypted_data)

    def receive_data(self):
        data = self.socket.recv(1024)
        # Here, the data from the server is assumed to be serialized
        return pickle.loads(data)
