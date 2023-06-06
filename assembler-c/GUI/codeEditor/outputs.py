import os
import tkinter as tk
from tkinter import messagebox


class AssemblerOutputs:
    """
    Initialize the AssemblerOutputs class.

    Args:
        text_widget (tk.Text): The text widget to display the outputs.
        user_files_dir (str): The directory where user files are stored.
        text_editor (AssemblyEditor): The instance of the AssemblyEditor class.

    """
    def __init__(self, text_widget, user_files_dir, text_editor):

        self._text_widget = text_widget
        self.user_files_dir = user_files_dir
        self.text_editor = text_editor  # store the text_editor instance
        self.binary_output_data = None
        self.ob_output_data = None

    def get_file_name(self):
        """
        Get the current file name from the AssemblyEditor instance.

        Returns:
            str: The current file name without the extension.

        """
        return os.path.splitext(os.path.basename(self.text_editor.get_current_file_path()))[0]

    def show_binary_output(self):
        """
        Display the binary output in the text widget.

        If a binary output file exists, its content is displayed in the text widget.
        If the file doesn't exist, an error message is displayed.

        """
        if self.binary_output_data is not None:
            self._text_widget.delete(1.0, tk.END)
            self._text_widget.insert(1.0, self.binary_output_data)
        else:
            messagebox.showerror("Error", "No binary output file found.")

    def show_base32_output(self):
        """
        Display the Base32 output in the text widget.

        If a Base32 output file exists, its content is displayed in the text widget.
        If the file doesn't exist, an error message is displayed.

        """
        if self.ob_output_data is not None:
            self._text_widget.delete(1.0, tk.END)
            self._text_widget.insert(1.0, self.ob_output_data)
        else:
            messagebox.showerror("Error", "No binary output file found.")
