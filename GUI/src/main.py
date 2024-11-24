import customtkinter as ctk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import time
import threading
from components.button_frame import ButtonFrame
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
      
        # Crea il frame per i pulsanti
        self.button_frame = ButtonFrame(self, self.start_plotting, self.stop_plotting, self.restore_plotting, self.empty_plotting)
        self.button_frame.pack(fill="x", padx=20, pady=(20, 0))
        
        # Crea il frame per visualizzare i grafici
        self.frame = ctk.CTkFrame(self)
        self.frame.pack(fill="both", expand=True, padx=20, pady=20)
        
        # Crea i grafici matplotlib (due grafici affiancati)
        self.fig, (self.ax1, self.ax2) = self.create_real_time_plots()

        # Crea il canvas per i grafici
        self.canvas = FigureCanvasTkAgg(self.fig, master=self.frame)
        self.canvas.get_tk_widget().pack(fill="both", expand=True)
        
        # Crea il frame per visualizzare i testi degli eventi
        self.text_frame_event = ctk.CTkFrame(self)
        self.text_frame_event.pack(fill="x", padx=20, pady=(20, 0))
        
        # Crea il widget Text per gli eventi
        self.text_event = tk.Text(self.text_frame_event, height=10)
        self.text_event.pack(fill="x", padx=20, pady=(20, 0))

        # Crea il frame per visualizzare i testi di debug
        self.text_frame_debug = ctk.CTkFrame(self)
        self.text_frame_debug.pack(fill="x", padx=20, pady=(20, 20))
        
        # Crea il widget Text per i messaggi di debug
        self.text_debug = tk.Text(self.text_frame_debug, height=10)
        self.text_debug.pack(fill="x", padx=20, pady=(20, 0))

        # Inizializza i dati
        self.x_data = []
        self.y_data = []

        self.x2_data = []
        self.y2_data = []

        self.arduino = ArduinoReader(port='COM3')
        self.arduino.connect()
        
        # Avvia un thread per simulare l'aggiornamento dei dati
        self.is_running = True
        self.update_thread = threading.Thread(target=self.update_data)
        self.update_thread.daemon = True
        self.update_thread.start()
        
        # Gestione della chiusura della finestra
        self.protocol("WM_DELETE_WINDOW", self.on_close)
    
    def create_real_time_plots(self):
        fig, (ax1, ax2) = plt.subplots(figsize=(12, 6), ncols=2)
        ax1.set_title("Temperature")
        ax1.set_xlabel("Time")
        ax1.set_ylabel("Value")

        ax2.set_title("Temperature")
        ax2.set_xlabel("Time")
        ax2.set_ylabel("Value")

        return fig, (ax1, ax2)
    
    def update_graph(self):
        self.ax1.clear()
        self.ax1.plot(self.x_data, self.y_data, label="Data", color="blue")
        self.ax1.set_title("Temperature")
        self.ax1.set_xlabel("Time")
        self.ax1.set_ylabel("Value")
        self.ax1.legend()

        self.ax2.clear()
        self.ax2.plot(self.x2_data, self.y2_data, label="Data", color="green")
        self.ax2.set_title("waste level")
        self.ax2.set_xlabel("Time")
        self.ax2.set_ylabel("Value")
        self.ax2.legend()
    
    def update_data(self):
        while self.is_running:
            try:
                result = self.arduino.read_data()

                if result is None:
                    continue

                var, debug, event = result

                message = var[0]

                # Aggiungi un nuovo punto ai dati
                self.x_data.append(time.time())
                self.y_data.append(int(message.data))


                message = var[1]
                self.x2_data.append(time.time())
                self.y2_data.append(int(message.data))
                
                # Aggiorna il testo visualizzato
                for debug_message in debug:
                    self.update_debug_text(f"DEBUG: {debug_message.data}")

                for event_message in event:
                    self.update_event_text(f"EVENT: {event_message.data}")
                
                # Mantieni solo gli ultimi 50 punti
                if len(self.x_data) > 50:
                    self.x_data = self.x_data[-50:]
                    self.y_data = self.y_data[-50:]


                if len(self.x2_data) > 50:
                    self.x2_data = self.x2_data[-50:]
                    self.y2_data = self.y2_data[-50:]
                
                # Aggiorna il grafico usando after() per thread safety
                self.after(0, self.safe_update)
                
                time.sleep(1)

            except RuntimeError:
                pass
    
    def update_debug_text(self, text):
        self.text_debug.insert(tk.END, text + "\n")
        self.text_debug.see(tk.END)
        self.limit_text(self.text_debug)

    def update_event_text(self, text):
        self.text_event.insert(tk.END, text + "\n")
        self.text_event.see(tk.END)
        self.limit_text(self.text_event)

    def limit_text(self, text_widget, max_lines=50):
        lines = text_widget.get(1.0, tk.END).splitlines()
        if len(lines) > max_lines:
            text_widget.delete(1.0, f"{len(lines) - max_lines + 1}.0")

    
    def safe_update(self):
        if self.is_running:
            self.update_graph()
            self.canvas.draw()
    
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

    def restore_plotting(self):
        # Implementa la logica per il pulsante Restore
        pass

    def empty_plotting(self):
        # Implementa la logica per il pulsante Empty
        pass
    
    def on_close(self):
        # Ferma il thread
        self.is_running = False
        
        # Aspetta che il thread termini
        self.update_thread.join(timeout=1.0)
        
        # Chiude la finestra e termina l'applicazione
        self.quit()
        self.destroy()

if __name__ == "__main__":
    app = RealTimePlotApp()
    app.mainloop()
