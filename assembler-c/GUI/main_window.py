import tkinter as tk
from GUI.codeEditor.assembly_editor import AssemblyEditor
from GUI.assembler_execution import AssemblerExecution
import tkinter.font as font
from codeEditor.outputs import AssemblerOutputs


class MainWindow(tk.Tk):
    """
    Create the main window of the application.

    This window contains an assembly code editor and various menu options.

    """
    def __init__(self):
        super().__init__()
        self.title('Assembler Code Editor')

        window_width = self.winfo_screenwidth() - 200
        window_height = self.winfo_screenheight() - 200

        x_coordinate = (self.winfo_screenwidth() - window_width) // 2
        y_coordinate = (self.winfo_screenheight() - window_height) // 2

        self.geometry("{0}x{1}+{2}+{3}".format(window_width, window_height, x_coordinate, y_coordinate))
        default_font = font.nametofont("TkDefaultFont")
        default_font.configure(family='Tahoma')

        self.file_menu = None
        self.edit_menu = None
        self.outputs_menu = None

        self.text_editor = AssemblyEditor(self)
        self.assembler_execution = AssemblerExecution(self, self.text_editor)

        self._create_menu()

    def _create_menu(self):
        """
        Create the menu bar with various options.

        The menu options include File, Edit, and Outputs.

        """
        menubar = tk.Menu(self, font=('Tahoma', 10))  # set font to Tahoma
        self.file_menu = tk.Menu(menubar, tearoff=0, font=('Tahoma', 10))  # set font to Tahoma
        self.file_menu.add_command(label="Open", command=self.text_editor.open_file)
        self.file_menu.add_command(label="Save", command=self.text_editor.save_file)
        self.file_menu.add_separator()
        self.file_menu.add_command(label="Exit", command=self.quit)
        menubar.add_cascade(label="File", menu=self.file_menu)

        self.edit_menu = tk.Menu(menubar, tearoff=0, font=('Tahoma', 10))  # set font to Tahoma
        self.edit_menu.add_command(label="Change Font", command=self.text_editor.change_font)
        self.edit_menu.add_command(label="Change Font Size", command=self.text_editor.change_font_size)
        self.edit_menu.add_command(label="Change Font Color", command=self.text_editor.change_font_color)
        menubar.add_cascade(label="Edit", menu=self.edit_menu)

        self.outputs_menu = tk.Menu(menubar, tearoff=0, font=('Tahoma', 10))
        self.outputs_menu.add_command(label="Binary Outputs", command=self.text_editor.show_binary_output,
                                      state="disabled")
        self.outputs_menu.add_command(label="Base32 Outputs", command=self.text_editor.show_base32_output,
                                      state="disabled")
        menubar.add_cascade(label="Outputs", menu=self.outputs_menu)
        self.assembler_execution.pack()

        self.config(menu=menubar)

    # def show_binary_output(self):
    #     """
    #     Show the binary outputs in the assembly editor.
    #
    #     This method is called when the "Binary Outputs" menu option is selected.
    #
    #     """
    #     self.text_editor.show_binary_output()
    #
    # def show_base32_output(self):
    #     """
    #     Show the Base32 outputs in the assembly editor.
    #
    #     This method is called when the "Base32 Outputs" menu option is selected.
    #
    #     """
    #     self.text_editor.show_base32_output()
    #
    # def enable_outputs(self):
    #     """
    #     Enable the outputs menu options.
    #
    #     This method is called when the assembly execution is successful.
    #
    #     """
    #     self.outputs_menu.entryconfig("Binary Outputs", state="normal")
    #     self.outputs_menu.entryconfig("Base32 Outputs", state="normal")
    #
    # def disable_outputs(self):
    #     """
    #     Disable the outputs menu options.
    #
    #     This method is called when the assembly execution fails.
    #
    #     """
    #     self.outputs_menu.entryconfig("Binary Outputs", state="disabled")
    #     self.outputs_menu.entryconfig("Base32 Outputs", state="disabled")

