import customtkinter as ctk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import time
import threading
from components.button_frame import ButtonFrame
from arduino import ArduinoReader

class RealTimePlotApp(ctk.CTk):
    def __init__(self):
        super().__init__()

        self.title("ARDUINO HMI")
        screen_width = self.winfo_screenwidth()
        screen_height = self.winfo_screenheight()
        window_width = int(screen_width * 0.8)
        window_height = int(screen_height * 0.8)
        self.geometry(f"{window_width}x{window_height}")
        
  
        
        # Crea il frame per i pulsanti
        self.button_frame = ButtonFrame(self, self.start_plotting, self.stop_plotting, self.restore_plotting, self.empty_plotting)
        self.button_frame.pack(fill="x", padx=20, pady=(20, 0))
        
        # Crea il frame per visualizzare il grafico
        self.frame = ctk.CTkFrame(self)
        self.frame.pack(fill="both", expand=True, padx=20, pady=20)
        
        # Crea il grafico matplotlib
        self.fig, self.ax = self.create_real_time_plot()
        
        # Crea il canvas per il grafico
        self.canvas = FigureCanvasTkAgg(self.fig, master=self.frame)
        self.canvas.get_tk_widget().pack(fill="both", expand=True)
        
        # Inizializza i dati
        self.x_data = []
        self.y_data = []

        self.arduino = ArduinoReader(port='COM3')
        self.arduino.connect()
        
        # Avvia un thread per simulare l'aggiornamento dei dati
        self.is_running = True
        self.update_thread = threading.Thread(target=self.update_data)
        self.update_thread.daemon = True
        self.update_thread.start()
        
        # Gestione della chiusura della finestra
        self.protocol("WM_DELETE_WINDOW", self.on_close)
    
    def create_real_time_plot(self):
        fig, ax = plt.subplots(figsize=(8, 6))
        ax.set_title("Real-Time Plot")
        ax.set_xlabel("Time")
        ax.set_ylabel("Value")
        ax.set
        return fig, ax
    
    def update_graph(self):
        self.ax.clear()
        self.ax.plot(self.x_data, self.y_data, label="Data", color="blue")
        self.ax.set_title("Real-Time Plot")
        self.ax.set_xlabel("Time")
        self.ax.set_ylabel("Value")
        self.ax.legend()
    
    def update_data(self):
        while self.is_running:
            try:
                message = self.arduino.read_data()
                if message is None or message.message_type != 0:
                    continue


                # Aggiungi un nuovo punto ai dati
                self.x_data.append(time.time())
                self.y_data.append(int(message.data))
                
                # Mantieni solo gli ultimi 50 punti
                if len(self.x_data) > 50:
                    self.x_data = self.x_data[-50:]
                    self.y_data = self.y_data[-50:]
                
                # Aggiorna il grafico usando after() per thread safety
                self.after(0, self.safe_update)
                
                time.sleep(1)
            except RuntimeError:
                # Gestisce l'errore se l'applicazione viene chiusa
                ciao = True
                
    
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