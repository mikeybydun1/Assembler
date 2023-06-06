import os
import subprocess
import threading
import tkinter as tk
from tkinter import ttk, messagebox
import time
from assembler_client import AssemblyClient
from tkinter.scrolledtext import ScrolledText


class AssemblerExecution(ttk.Button):
    def __init__(self, parent, text_editor, makefile_path):

        super().__init__(parent, text="Assembler", command=self.assemble)
        self.parent = parent
        self.text_editor = text_editor
        self.makefile_path = makefile_path
        self.progress_bar = None
        self.result_window = None

        self.style = ttk.Style()
        self.style.configure(
            "Custom.TButton",
            font=("Arial", 14),
            foreground="#46574d",
            background="#007acc",
            width=15,
            height=3
        )
        self.configure(style="Custom.TButton")

    def assemble(self):
        if not self.text_editor.is_saved or self.text_editor.is_empty():
            messagebox.showwarning("Unsaved changes or empty file", "Please save your work or enter some code before assembling.")
            return

        self.progress_bar = ttk.Progressbar(self.parent, mode='indeterminate')
        self.progress_bar.pack(pady=10)
        self.progress_bar.start()

        threading.Thread(target=self._run_executable).start()

    def _run_makefile(self):
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
            if rc == 0:
                self._run_executable()
        except subprocess.CalledProcessError as e:
            print(f"Makefile execution failed: {e}")
        finally:
            time.sleep(2)
            self.progress_bar.stop()
            self.progress_bar.destroy()

    def _show_result_window(self, content):
        if self.result_window:
            self.result_window.destroy()

        self.result_window = tk.Toplevel(self.parent)
        self.result_window.title("Assembler Results")

        text_widget = ScrolledText(self.result_window, width=80, height=30, font=("Courier New", 12))
        text_widget.pack(fill="both", expand=True)
        text_widget.insert("1.0", content)
        text_widget.configure(state="disabled")

    def _run_executable(self):
        file_path = self.text_editor.get_current_file_path()
        if file_path:
            file_name = os.path.splitext(os.path.basename(file_path))[0]

            with open(file_path, 'r') as file:
                file_content = file.read()

            # Create a client and send the file content to the server
            self.client = AssemblyClient()  # Initialize self.client here
            self.client.send_file(file_name, file_content)

            # Receive the response from the server
            result = self.client.receive_data()
            self._show_result_window(result.stdout)

            print(f"Server response: {result}")
