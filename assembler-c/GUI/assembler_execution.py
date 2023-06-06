import os
import pickle
import threading
import tkinter as tk
from tkinter import ttk, messagebox
from GUI.communication.assembler_client import AssemblyClient
from tkinter.scrolledtext import ScrolledText
from GUI.communication.encrypt_decrypt import decrypt_data
from PIL import Image, ImageTk


class AssemblerExecution(ttk.Button):
    def __init__(self, parent, text_editor):

        super().__init__(parent, text="Run Assembler", command=self.assemble)
        self.parent = parent
        self.text_editor = text_editor
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

    def _show_result_window(self, content):
        if self.result_window:
            self.result_window.destroy()

        self.result_window = tk.Toplevel(self.parent)
        self.result_window.title("Assembler Results")

        text_widget = ScrolledText(self.result_window, width=80, height=30, font=("Courier New", 12))
        text_widget.pack(fill="both", expand=True)
        text_widget.insert("1.0", content)
        text_widget.configure(state="disabled")

    def show_success_message(self):

        success_window = tk.Toplevel(self.parent)
        success_window.title('Success!')
        success_window.geometry('400x300+500+300')
        success_window.configure(bg='#002955')

        # Load an image using Pillow library and create PhotoImage object
        image = Image.open("path_to_your_image")
        photo = ImageTk.PhotoImage(image)
        image_label = tk.Label(success_window, image=photo, bg='#002955')
        image_label.image = photo  # Keep a reference
        image_label.pack(pady=(20, 10))

        # Message
        success_label = tk.Label(success_window,
                                 text='Server succeeded to assemble your code!\nNow you can look on the outputs files',
                                 font=('Arial', 14, 'bold'), fg='white', bg='#002955', pady=20)

        success_label.pack(fill='x')

        # Decorative Frame
        frame = tk.Frame(success_window, bg='#4CAF50')
        frame.pack(fill='x')

        # Button
        ok_button = tk.Button(frame, text='OK', command=success_window.destroy, fg='#002955', bg='#4CAF50', padx=20,
                              pady=10, font=('Arial', 12, 'bold'))
        ok_button.pack(pady=(20, 10))

        success_window.grab_set()

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

            if result[1] is None:
                print('Server failed to run the assembler on the given code.')
                decrypted_result = pickle.loads(decrypt_data(result[0]))
                self._show_result_window(decrypted_result.stdout)

            else:

                decrypt_outputs = pickle.loads(decrypt_data(result[1]))

                ob_output = decrypt_outputs['ob_data']
                bin_output = decrypt_outputs['bin_data']

                print('Server succeeded to assemble your code! Now you can look on the outputs files')
                self.text_editor.enable_outputs()
                self.text_editor.outputs.binary_output_data = bin_output
                self.text_editor.outputs.ob_output_data = ob_output
                self.show_success_message()

        self.progress_bar.stop()
        self.progress_bar.destroy()
