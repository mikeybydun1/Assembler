import socket
import pickle
import subprocess

from GUI.encrypt_decrypt import decrypt_data
import os


class AssemblyServer:
    def __init__(self, host="localhost", port=5000):
        self.host = host
        self.port = port
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(1)
        self.makefile_path = 'D:/Desktop/Assembler/assembler-c/src/makefile.mk'
        self.server_working_path = 'D:/Desktop/Assembler/assembler-c/server'

    def start(self):
        while True:
            print("Server is waiting for client connection...")
            client_socket, addr = self.server_socket.accept()
            print(f"Client {addr} connected")
            data = client_socket.recv(1024)

            decrypted_data = decrypt_data(data)
            if decrypted_data is None:
                print("Data decryption failed.")
                continue

            decrypted_data = pickle.loads(decrypted_data)

            file_name = decrypted_data.get("file_name")
            file_content = decrypted_data.get("file_content")

            file_path = f"D:/Desktop/Assembler/assembler-c/server/{file_name}.am"
            with open(file_path, "w") as file:
                file.write(file_content)

            result = self.run_assembler(file_name)

            client_socket.sendall(pickle.dumps(result))

            print(f"Result sent back to client {addr}")
            client_socket.close()

    def run_assembler(self, file_name):
        os.chdir(os.path.dirname(self.makefile_path))
        try:
            process = subprocess.Popen(['mingw32-make', '-f', os.path.basename(self.makefile_path)],
                                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            while True:
                output = process.stdout.readline()
                if output == b'' and process.poll() is not None:
                    break
                if output:
                    print(output.decode('utf-8'))
            rc = process.poll()
        except subprocess.CalledProcessError as e:
            print(f"Makefile execution failed: {e}")

        run_assembler_command = f'./a {file_name}'
        result = subprocess.run(["C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe", "-Command",
                                 run_assembler_command], cwd=self.server_working_path, check=True, capture_output=True,
                                text=True)
        return result


if __name__ == "__main__":
    server = AssemblyServer()
    server.start()