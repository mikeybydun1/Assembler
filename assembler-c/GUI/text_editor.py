import tkinter as tk
from tkinter import filedialog, messagebox, simpledialog, font
from tkinter.colorchooser import askcolor


class TextEditor(tk.Frame):
    def __init__(self, parent):
        super().__init__(parent)
        self._create_text_widget()

        self.font_actual = {'family': 'Calibri', 'size': 12}
        self.is_saved = True
        self.current_file_path = ''

    def _create_text_widget(self):
        self._text_widget = tk.Text(self, wrap='word', undo=True, font=('Calibri', 12))
        self._text_widget.pack(fill='both', expand=True)
        self.pack(fill='both', expand=True)

        self._text_widget.bind('<<Modified>>', self._set_unsaved)

    def open_file(self):
        file_path = filedialog.askopenfilename(filetypes=(('Assembler files', '*.am'),))
        if file_path:
            file_contents = open(file_path, encoding='latin-1').read()
            self._text_widget.insert('1.0', file_contents)
            self.is_saved = True
            self.current_file_path = file_path

    def save_file(self):
        file_name = filedialog.asksaveasfilename(
            initialdir='D:/Desktop/Assembler/assembler-c/src/userFiles',
            defaultextension='.am',
            filetypes=(('Assembler files', '*.am'),)
        )
        if file_name:
            file_contents = self._text_widget.get('1.0', 'end-1c')
            with open(file_name, 'w') as file:
                file.write(file_contents)
            self.is_saved = True
            self.current_file_path = file_name

    def change_font(self):
        available_fonts = list(font.families())
        chosen_font = simpledialog.askstring("Change font", "Choose font", initialvalue=self.font_actual['family'])
        if chosen_font in available_fonts:
            self.font_actual['family'] = chosen_font
            self._text_widget.configure(font=self.font_actual)

    def change_font_size(self):
        size = simpledialog.askinteger("Change font size", "Enter font size", initialvalue=self.font_actual['size'], minvalue=1)
        if size:
            self.font_actual['size'] = size
            self._text_widget.configure(font=self.font_actual)

    def change_font_color(self):
        color = askcolor()[1]
        if color:
            self._text_widget.config(foreground=color)

    def _set_unsaved(self, event=None):
        if self._text_widget.edit_modified():
            self.is_saved = False
            self._text_widget.edit_modified(False)

    def is_empty(self):
        return self._text_widget.compare('end-1c', '==', '1.0')

    def get_current_file_path(self):
        return self.current_file_path

