import tkinter as tk
from GUI.text_editor import TextEditor
from assembler_button import AssemblerButton


class MainWindow(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title('Assembler Text Editor')
        self.geometry('900x600')
        self.text_editor = TextEditor(self)
        self._create_menu()

    def _create_menu(self):
        menubar = tk.Menu(self)
        file_menu = tk.Menu(menubar, tearoff=0)
        file_menu.add_command(label="Open", command=self.text_editor.open_file)
        file_menu.add_command(label="Save", command=self.text_editor.save_file)
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=self.quit)
        menubar.add_cascade(label="File", menu=file_menu)

        edit_menu = tk.Menu(menubar, tearoff=0)
        edit_menu.add_command(label="Change Font", command=self.text_editor.change_font)
        edit_menu.add_command(label="Change Font Size", command=self.text_editor.change_font_size)
        edit_menu.add_command(label="Change Font Color", command=self.text_editor.change_font_color)
        menubar.add_cascade(label="Edit", menu=edit_menu)

        assembler_button = AssemblerButton(self, self.text_editor, 'D:/Desktop/Assembler/assembler-c/src/makefile.mk')
        assembler_button.pack()

        self.config(menu=menubar)
