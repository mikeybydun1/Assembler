import tkinter as tk
from tkinter.colorchooser import askcolor
from tkinter.filedialog import askopenfilename, asksaveasfilename


class UI:
    BG_COLOR = 'white'
    FONT = ("Tahoma", 12)

    def _create_widget(self, widget_class, parent, **options):
        return widget_class(parent, bg=self.BG_COLOR, font=self.FONT, **options)

    def ask_color(self):
        color = askcolor()[1]
        if color:
            return color

    def open_file(self):
        filepath = askopenfilename(
            filetypes=[("Text Files", "*.txt"), ("All Files", "*.*")]
        )
        if filepath:
            with open(filepath, "r") as input_file:
                text = input_file.read()
                return text

    def save_file(self, text):
        filepath = asksaveasfilename(
            defaultextension="txt",
            filetypes=[("Text Files", "*.txt"), ("All Files", "*.*")],
        )
        if filepath:
            with open(filepath, "w") as output_file:
                output_file.write(text)
