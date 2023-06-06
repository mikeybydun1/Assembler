import tkinter as tk
from tkinter import filedialog, simpledialog, font
from tkinter.colorchooser import askcolor
from GUI.codeEditor.outputs import AssemblerOutputs


class AssemblyEditor(tk.Frame):
    """
    A text editor widget for editing assembly code.

    Attributes:
        parent (tk.Tk or tk.Frame): The parent widget.

    Methods:
        __init__(self, parent):
            Initializes a new instance of the AssemblyEditor class.
            Args:
                parent (tk.Tk or tk.Frame): The parent widget.

        open_file(self):
            Opens a file and inserts its contents into the text editor.

        save_file(self):
            Saves the contents of the text editor to a file.

        change_font(self):
            Changes the font of the text editor.

        change_font_size(self):
            Changes the font size of the text editor.

        change_font_color(self):
            Changes the font color of the text editor.

        is_empty(self):
            Checks if the text editor is empty.

        get_current_file_path(self):
            Retrieves the current file path.

        enable_outputs(self):
            Enables the outputs feature.

        disable_outputs(self):
            Disables the outputs feature.

        show_binary_output(self):
            Shows the binary output in the outputs area.

        show_base32_output(self):
            Shows the Base32 output in the outputs area.
    """
    def __init__(self, parent):
        """
        Initializes a new instance of the AssemblyEditor class.

        Args:
            parent (tk.Tk or tk.Frame): The parent widget.
        """
        super().__init__(parent)
        self._create_text_widget()
        self.main_application = parent

        self.font_actual = {'family': 'Tahoma', 'size': 12}
        self.is_saved = True
        self.current_file_path = ''

        self.outputs_enabled = False

        self.outputs = AssemblerOutputs(self._text_widget, "D:/Desktop/Assembler/assembler-c/src/userFiles", self)

    def _create_text_widget(self):
        """
        Creates the text widget for the assembly editor.

        Returns:
            None
        """
        self._text_widget = tk.Text(self, wrap='word', undo=True, font=('Tahoma', 12))
        self._text_widget.pack(fill='both', expand=True)
        self.pack(fill='both', expand=True)

        self._text_widget.bind('<<Modified>>', self._set_unsaved)

    def get_user_files_dir(self):
        # This method needs to be updated to provide the correct path
        return "D:/Desktop/Assembler/assembler-c/src/userFiles"

    def open_file(self):
        """
        Opens a file and inserts its contents into the text editor.
        """
        file_path = filedialog.askopenfilename(filetypes=(('Assembler files', '*.am'),))
        if file_path:
            file_contents = open(file_path, encoding='latin-1').read()
            self._text_widget.insert('1.0', file_contents)
            self.is_saved = True
            self.current_file_path = file_path

    def save_file(self):
        """
        Saves the contents of the text editor to a file.
        """
        file_name = filedialog.asksaveasfilename(
            initialdir=self.get_user_files_dir(),
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
        """
        Changes the font of the text editor.
        """
        available_fonts = list(font.families())
        chosen_font = simpledialog.askstring("Change font", "Choose font", initialvalue=self.font_actual['family'])
        if chosen_font in available_fonts:
            self.font_actual['family'] = chosen_font
            self._text_widget.configure(font=self.font_actual)

    def change_font_size(self):
        """
        Changes the font size of the text editor.
        """
        size = simpledialog.askinteger("Change font size", "Enter font size", initialvalue=self.font_actual['size'], minvalue=1)
        if size:
            self.font_actual['size'] = size
            self._text_widget.configure(font=self.font_actual)

    def change_font_color(self):
        """
        Changes the font color of the text editor.
        """
        color = askcolor()[1]
        if color:
            self._text_widget.config(foreground=color)

    def _set_unsaved(self, event=None):
        """
        Marks the text editor as unsaved if there are modifications.

        Args:
            event (tk.Event, optional): The event that triggered the method.

        Returns:
            None
        """
        if self._text_widget.edit_modified():
            self.is_saved = False
            self._text_widget.edit_modified(False)

    def is_empty(self):
        """
        Checks if the text editor is empty.

        Returns:
            bool: True if the text editor is empty, False otherwise.
        """
        return self._text_widget.compare('end-1c', '==', '1.0')

    def get_current_file_path(self):
        """
        Retrieves the current file path.

        Returns:
            str: The current file path.
        """
        return self.current_file_path

    def enable_outputs(self):
        """
        Enables the outputs feature.
        """
        self.outputs_enabled = True
        self.main_application.outputs_menu.entryconfig("Binary Outputs", state="normal")
        self.main_application.outputs_menu.entryconfig("Base32 Outputs", state="normal")

    def disable_outputs(self):
        """
        Disables the outputs feature.
        """
        self.outputs_enabled = False
        self.main_application.outputs_menu.entryconfig("Binary Outputs", state="disabled")
        self.main_application.outputs_menu.entryconfig("Base32 Outputs", state="disabled")

    def show_binary_output(self):
        """
        Shows the binary output in the outputs area.
        """
        self.outputs.show_binary_output()

    def show_base32_output(self):
        """
        Shows the Base32 output in the outputs area.
        """
        self.outputs.show_base32_output()



