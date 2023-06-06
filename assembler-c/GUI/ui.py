import tkinter as tk
from tkinter.colorchooser import askcolor
from tkinter.filedialog import askopenfilename, asksaveasfilename


class UI:
    BG_COLOR = 'white'
    FONT = ("Tahoma", 12)

    def _create_widget(self, widget_class, parent, **options):
        """
        Create a widget with the specified widget class and options.

        Args:
            widget_class: The class of the widget to create.
            parent: The parent widget.
            **options: Additional options to configure the widget.

        Returns:
            The created widget.

        """
        return widget_class(parent, bg=self.BG_COLOR, font=self.FONT, **options)

    def ask_color(self):
        """
        Open a color chooser dialog and return the selected color.

        Returns:
            The selected color in hexadecimal format, or None if no color is selected.

        """
        color = askcolor()[1]
        if color:
            return color

    def open_file(self):
        """
        Open a file dialog to select a file to open.

        Returns:
            The contents of the selected file as a string, or None if no file is selected.

        """
        filepath = askopenfilename(
            filetypes=[("Text Files", "*.txt"), ("All Files", "*.*")]
        )
        if filepath:
            with open(filepath, "r") as input_file:
                text = input_file.read()
                return text

    def save_file(self, text):
        """
        Open a file dialog to select a file to save.

        Args:
            text: The text to save.

        Returns:
            None.

        """
        filepath = asksaveasfilename(
            defaultextension="txt",
            filetypes=[("Text Files", "*.txt"), ("All Files", "*.*")],
        )
        if filepath:
            with open(filepath, "w") as output_file:
                output_file.write(text)
