import customtkinter as ctk

class ButtonFrame(ctk.CTkFrame):
    def __init__(self, master, start_command, stop_command, disconnect_command , restore_command, empty_command):
        super().__init__(master)
        
        self.start_button = ctk.CTkButton(self, text="Start plot or connect", command=start_command)
        self.start_button.pack(side="left", padx=10)
        
        self.stop_button = ctk.CTkButton(self, text="Stop plot", command=stop_command)
        self.stop_button.pack(side="left", padx=10)

        self.disconnect_button = ctk.CTkButton(self, text="Disconnect", command=disconnect_command)
        self.disconnect_button.pack(side="left", padx=10)

        self.restore_button = ctk.CTkButton(self, text="Restore", command=restore_command)
        self.restore_button.pack(side="right", padx=10)

        self.empty_button = ctk.CTkButton(self, text="Empty", command=empty_command)
        self.empty_button.pack(side="right", padx=10)