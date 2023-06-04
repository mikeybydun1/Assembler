import os
import subprocess
import threading
import tkinter as tk
from tkinter import ttk, messagebox


class AssemblerButton(ttk.Button):
    def __init__(self, parent, text_editor, makefile_path):
        super().__init__(parent, text="Assembler", command=self.assemble)
        self.parent = parent
        self.text_editor = text_editor
        self.makefile_path = makefile_path
        self.output_window = None
        self.output_text = None

    def assemble(self):
        if not self.text_editor.is_saved or self.text_editor.is_empty():
            messagebox.showwarning("Unsaved changes or empty file", "Please save your work or enter some code before assembling.")
            return

        self.output_window = tk.Toplevel(self.parent)
        self.output_window.title("Assembler Output")
        self.output_text = tk.Text(self.output_window, state='disabled')
        self.output_text.pack(expand=True, fill='both')

        threading.Thread(target=self._run_makefile).start()

    def _run_makefile(self):
        os.chdir(os.path.dirname(self.makefile_path))
        try:
            process = subprocess.Popen(['mingw32-make', '-f', os.path.basename(self.makefile_path)],
                                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            while True:
                output = process.stdout.readline()
                if output == b'' and process.poll() is not None:
                    break
                if output:
                    self._update_output_text(output.decode('utf-8'))
            rc = process.poll()
            if rc == 0:
                self._run_executable()
        except subprocess.CalledProcessError as e:
            print(f"Makefile execution failed: {e}")

    def _update_output_text(self, output):
        self.output_text.configure(state='normal')
        self.output_text.insert('end', output)
        self.output_text.configure(state='disabled')
        self.output_text.see('end')

    def _run_executable(self):
        file_path = self.text_editor.get_current_file_path()
        if file_path:
            file_name = os.path.splitext(os.path.basename(file_path))[0]
            executable_path = os.path.join(os.path.dirname(file_path), '..', 'a.exe')
            user_files_dir = os.path.dirname(file_path)

            run_assembler_command = f'./a {file_name}'
            # change_directory_command = f'cd {user_files_dir}'

            try:
                result = subprocess.run(["C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe", "-Command", run_assembler_command], cwd=user_files_dir, check=True, capture_output=True, text=True)

                print(result.stdout)
            except subprocess.CalledProcessError as e:
                print(f"Command execution failed: {e}")
                print(f"Command return code: {e.returncode}")
                if e.stdout:
                    print(f"Command output: {e.stdout}")
                if e.stderr:
                    print(f"Command error: {e.stderr}")











