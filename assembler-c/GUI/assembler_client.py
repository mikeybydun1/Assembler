import socket
import pickle
from encrypt_decrypt import encrypt_data


class AssemblyClient:
    """
    A client class for interacting with the assembly server.

    Attributes:
        host (str): The host address of the server.
        port (int): The port number of the server.
        socket (socket.socket): The socket object for communication with the server.

    Methods:
        __init__(self, host="localhost", port=5000):
            Initializes a new instance of the AssemblyClient class.
            Args:
                host (str): The host address of the server. Defaults to "localhost".
                port (int): The port number of the server. Defaults to 5000.

        send_file(self, file_name, file_content):
            Sends a file to the server.
            Args:
                file_name (str): The name of the file.
                file_content (str): The content of the file.

        receive_data(self):
            Receives data from the server.
            Returns:
                The deserialized data received from the server.
    """
    def __init__(self, host="localhost", port=5000):
        """
        Initializes a new instance of the AssemblyClient class.

        Args:
            host (str): The host address of the server. Defaults to "localhost".
            port (int): The port number of the server. Defaults to 5000.
        """
        self.host = host
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))

    def send_file(self, file_name, file_content):
        """
        Sends a file to the server.

        Args:
            file_name (str): The name of the file.
            file_content (str): The content of the file.
        """
        data = {
            "file_name": file_name,
            "file_content": file_content
        }

        # Serialize and encrypt the data
        encrypted_data = encrypt_data(pickle.dumps(data))

        self.socket.sendall(encrypted_data)

    def receive_data(self):
        """
        Receives data from the server.

        Returns:
            The deserialized data received from the server.
        """
        data = self.socket.recv(1024)
        # Here, the data from the server is assumed to be serialized
        return pickle.loads(data)
