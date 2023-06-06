import os
import tkinter as tk
from tkinter import messagebox


class AssemblerOutputs:
    def __init__(self, text_widget, user_files_dir, text_editor):
        self._text_widget = text_widget
        self.user_files_dir = user_files_dir
        self.text_editor = text_editor  # store the text_editor instance

    def get_file_name(self):
        return os.path.splitext(os.path.basename(self.text_editor.get_current_file_path()))[0]

    def show_binary_output(self):
        binary_file_path = os.path.join(self.user_files_dir, self.get_file_name() + ".bin")
        if os.path.isfile(binary_file_path):
            with open(binary_file_path, "rb") as file:
                binary_content = file.read()
            self._text_widget.delete(1.0, tk.END)
            self._text_widget.insert(1.0, binary_content)
        else:
            messagebox.showerror("Error", "No binary output file found.")

    def show_base32_output(self):
        base32_file_path = os.path.join(self.user_files_dir, self.get_file_name() + ".ob")
        if os.path.isfile(base32_file_path):
            with open(base32_file_path, "r") as file:
                base32_content = file.read()
            self._text_widget.delete(1.0, tk.END)
            self._text_widget.insert(1.0, base32_content)
        else:
            messagebox.showerror("Error", "No base32 output file found.")
