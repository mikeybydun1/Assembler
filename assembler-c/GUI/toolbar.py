import tkinter as tk


class OutputsToolBar:
    def __init__(self, text_editor):  # now text_editor is the TextEditor instance
        self.text_editor = text_editor  # save it as an attribute of TextEditorToolBar

        self.outputs_button = tk.Menubutton(self.text_editor, text="Outputs", state="disabled")
        self.outputs_menu = tk.Menu(self.outputs_button, tearoff=0)
        self.outputs_button.config(menu=self.outputs_menu)

        self.outputs_menu.add_command(label="Binary Outputs", command=self.text_editor.show_binary_output, state="disabled")
        self.outputs_menu.add_command(label="Base32 Outputs", command=self.text_editor.show_base32_output, state="disabled")

    def enable_outputs(self):
        self.outputs_menu.entryconfig("Binary Outputs", state="normal")
        self.outputs_menu.entryconfig("Base32 Outputs", state="normal")

    def disable_outputs(self):
        self.outputs_menu.entryconfig("Binary Outputs", state="disabled")
        self.outputs_menu.entryconfig("Base32 Outputs", state="disabled")
