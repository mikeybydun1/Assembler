import tkinter as tk
from GUI.assembly_editor import AssemblyEditor
from GUI.assembler_execution import AssemblerExecution
import tkinter.font as font
import socket


class MainWindow(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title('Assembler Text Editor')

        window_width = self.winfo_screenwidth() - 200
        window_height = self.winfo_screenheight() - 200

        x_coordinate = (self.winfo_screenwidth() - window_width) // 2
        y_coordinate = (self.winfo_screenheight() - window_height) // 2

        self.geometry("{0}x{1}+{2}+{3}".format(window_width, window_height, x_coordinate, y_coordinate))
        default_font = font.nametofont("TkDefaultFont")
        default_font.configure(family='Tahoma')

        self.text_editor = AssemblyEditor(self)
        self._create_menu()

    def _create_menu(self):
        menubar = tk.Menu(self, font=('Tahoma', 10))  # set font to Tahoma
        file_menu = tk.Menu(menubar, tearoff=0, font=('Tahoma', 10))  # set font to Tahoma
        file_menu.add_command(label="Open", command=self.text_editor.open_file)
        file_menu.add_command(label="Save", command=self.text_editor.save_file)
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=self.quit)
        menubar.add_cascade(label="File", menu=file_menu)

        edit_menu = tk.Menu(menubar, tearoff=0, font=('Tahoma', 10))  # set font to Tahoma
        edit_menu.add_command(label="Change Font", command=self.text_editor.change_font)
        edit_menu.add_command(label="Change Font Size", command=self.text_editor.change_font_size)
        edit_menu.add_command(label="Change Font Color", command=self.text_editor.change_font_color)
        menubar.add_cascade(label="Edit", menu=edit_menu)

        self.outputs_menu = tk.Menu(menubar, tearoff=0, font=('Tahoma', 10))  # set font to Tahoma
        self.outputs_menu.add_command(label="Binary Outputs", command=self.text_editor.show_binary_output,
                                      state="disabled")
        self.outputs_menu.add_command(label="Base32 Outputs", command=self.text_editor.show_base32_output,
                                      state="disabled")
        menubar.add_cascade(label="Outputs", menu=self.outputs_menu)

        assembler_execution = AssemblerExecution(self, self.text_editor, 'D:/Desktop/Assembler/assembler-c/src/makefile.mk')
        assembler_execution.pack()

        self.config(menu=menubar)

    def show_binary_output(self):
        self.text_editor.show_binary_output()

    def show_base32_output(self):
        self.text_editor.show_base32_output()

    def enable_outputs(self):
        self.outputs_menu.entryconfig("Binary Outputs", state="normal")
        self.outputs_menu.entryconfig("Base32 Outputs", state="normal")

    def disable_outputs(self):
        self.outputs_menu.entryconfig("Binary Outputs", state="disabled")
        self.outputs_menu.entryconfig("Base32 Outputs", state="disabled")

