import customtkinter as ctk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import time
import threading
from components.button_frame import ButtonFrame
from components.double_plot import create_real_time_plots
from arduino import ArduinoReader
import tkinter as tk

class RealTimePlotApp(ctk.CTk):
    def __init__(self):
        super().__init__()

        self.title("ARDUINO HMI")
        screen_width = self.winfo_screenwidth()
        screen_height = self.winfo_screenheight()
        window_width = int(screen_width)
        window_height = int(screen_height)

        # Posiziona la finestra al centro dello schermo
        x_pos = int((screen_width - window_width) / 2)
        y_pos = int((screen_height - window_height) / 2)
        self.geometry(f"{window_width}x{window_height}+{x_pos}+{y_pos}")
      

        # Crea l'etichetta per lo stato della connessione
        self.connection_status = ctk.CTkLabel(self, text="Stato connessione: Disconnesso")
        self.connection_status.pack(pady=(10, 0))
        # Crea il frame per i pulsanti
        self.button_frame = ButtonFrame(self, self.start_plotting, self.stop_plotting, self.disconnect, self.restore, self.empty)
        self.button_frame.pack(fill="x", padx=20, pady=(20, 0))
        
        # Crea il frame per visualizzare i grafici
        self.frame = ctk.CTkFrame(self)
        self.frame.pack(fill="both", expand=True, padx=20, pady=20)
        
        # Crea i grafici matplotlib (due grafici affiancati)
        self.fig, (self.ax1, self.ax2) = create_real_time_plots()

        # Crea il canvas per i grafici
        self.canvas = FigureCanvasTkAgg(self.fig, master=self.frame)
        self.canvas.get_tk_widget().pack(fill="both", expand=True)
        
        # Crea il frame per visualizzare i testi degli eventi
        self.text_frame_event = ctk.CTkFrame(self)
        self.text_frame_event.pack(fill="x", padx=20, pady=(20, 0))
        
        # Crea il widget Text per gli eventi
        self.text_event = tk.Text(self.text_frame_event, height=10, state=tk.DISABLED)
        self.text_event.pack(fill="x", padx=20, pady=(20, 0))

        # Crea il frame per visualizzare i testi di debug
        self.text_frame_debug = ctk.CTkFrame(self)
        self.text_frame_debug.pack(fill="x", padx=20, pady=(20, 20))
        
        # Crea il widget Text per i messaggi di debug
        self.text_debug = tk.Text(self.text_frame_debug, height=10, state=tk.DISABLED)
        self.text_debug.pack(fill="x", padx=20, pady=(20, 0))

    

        # Inizializza i dati
        self.x_data = []
        self.y_data = []

        self.x2_data = []
        self.y2_data = []

        self.data_to_read = {"temperature": 0, "level": 1}
        self.data_to_write = {"restore": 0, "empty": 1}

        self.var = []
        self.debug = []
        self.event = []

        self.arduino = ArduinoReader()
        self.arduino.connect()

        self.is_running = True
        self.update_thread = threading.Thread(target=self.update_data)
        self.update_thread.daemon = True
        self.update_thread.start()
        
        self.protocol("WM_DELETE_WINDOW", self.on_close)
        
        self.debug_counter = 0
        self.event_counter = 0
        
    def disconnect(self):
        self.arduino.disconnect()
        self.stop_plotting()
                # Aggiorna lo stato della connessione
        if self.arduino.is_connected():
            self.connection_status.configure(text="Stato connessione: Connesso")
        else:
            self.connection_status.configure(text="Stato connessione: Disconnesso")
        self.update_idletasks()

    
    def update_data(self):
        while self.is_running:
            try:
                if self.arduino.is_connected():
                    result = self.arduino.read_data()

                    if result is None:
                        continue

                    self.var, self.debug, self.event = result

                    temperature = None
                    for var in self.var:
                        if var.id == self.data_to_read["temperature"]:
                            temperature = var

                    level = None
                    for var in self.var:
                        if var.id == self.data_to_read["level"]:
                            level = var

                    if temperature is not None:
                        self.x_data.append(time.time())
                        self.y_data.append(int(temperature.data))

                        if len(self.x_data) > 50:
                            self.x_data = self.x_data[-50:]
                            self.y_data = self.y_data[-50:]

                    if level is not None:
                        self.x2_data.append(time.time())
                        self.y2_data.append(float(level.data))
                        if len(self.x2_data) > 50:
                            self.x2_data = self.x2_data[-50:]
                            self.y2_data = self.y2_data[-50:]

                    # Aggiorna la gui in modo sicuro dal thread principale
                    self.after(0, self.safe_update)
                    
                    time.sleep(0.25)
                else:
                    self.arduino.connect()
            except RuntimeError:
                pass

    def safe_update(self):
        if self.is_running:
            self.update_graph()

            for debug_message in self.debug:
                self.update_debug_text(f"DEBUG: {debug_message.data}")

            for event_message in self.event:
                self.update_event_text(f"EVENT: {event_message.data}")

            # Aggiorna lo stato della connessione
            if self.arduino.is_connected():
                self.connection_status.configure(text="Stato connessione: Connesso")
            else:
                self.connection_status.configure(text="Stato connessione: Disconnesso")

    def update_graph(self):
        self.ax1.clear()
        self.ax1.plot(self.x_data, self.y_data, label="Data", color="blue")
        self.ax1.set_title("Temperature")
        self.ax1.set_xlabel("Time")
        self.ax1.set_ylabel("Value")
        self.ax1.legend()

        self.ax2.clear()
        self.ax2.plot(self.x2_data, self.y2_data, label="Data", color="green")
        self.ax2.set_title("Waste Level")
        self.ax2.set_xlabel("Time")
        self.ax2.set_ylabel("Value")
        self.ax2.legend()
        self.canvas.draw()

    def update_debug_text(self, text):
        self.debug_counter += 1
        self.text_debug.configure(state=tk.NORMAL)
        self.text_debug.insert(tk.END, f"DEBUG {self.debug_counter}: {text}\n")
        self.text_debug.see(tk.END)
        self.limit_text(self.text_debug)
        self.text_debug.configure(state=tk.DISABLED)

    def update_event_text(self, text):
        self.event_counter += 1
        self.text_event.configure(state=tk.NORMAL)
        self.text_event.insert(tk.END, f"EVENT {self.event_counter}: {text}\n")
        self.text_event.see(tk.END)
        self.limit_text(self.text_event)
        self.text_event.configure(state=tk.DISABLED)

    def limit_text(self, text_widget, max_lines=50):
        lines = text_widget.get(1.0, tk.END).splitlines()
        if len(lines) > max_lines:
            text_widget.delete(1.0, f"{len(lines) - max_lines + 1}.0")
    
    def restore(self):
        if self.arduino.is_connected():
            self.arduino.write_data(1, self.data_to_write["restore"])

    def empty(self):
        if self.arduino.is_connected():
            self.arduino.write_data(1, self.data_to_write["empty"])

    def start_plotting(self):
        self.is_running = True
        if not self.update_thread.is_alive():
            self.update_thread = threading.Thread(target=self.update_data)
            self.update_thread.daemon = True
            self.update_thread.start()
    
    def stop_plotting(self):
        self.is_running = False
        self.update_thread.join(timeout=1.0)
        self.x_data.clear()
        self.y_data.clear()

    def on_close(self):
        self.is_running = False
        self.update_thread.join(timeout=1.0)
        self.quit()
        self.destroy()

if __name__ == "__main__":
    app = RealTimePlotApp()
    app.mainloop()