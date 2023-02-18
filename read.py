#!/usr/bin/python
import serial
import serial.tools.list_ports as p

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.widgets import Button


import random
from itertools import count

ports = p.comports()
port=[]
for i in ports:
    port.append(i.device)

ser = serial.Serial(port[0],9600,timeout=5)
ser.reset_input_buffer()  



#x_vals = [0,1,2,3,4,5]
#y_vals = [0,1,3,2,3,5]
#plt.plot(x_vals,y_vals)
#plt.tight_layout()
#plt.show()


index = count()
x_vals = []
y_vals=[]
another_vals=[]
oldlista = []


def reset_plot(event):
    plt.cla()
    x_vals = []
    y_vals = []
    another_vals = []



def animate(i):
    try:   
        ser_bytes = ser.readline().decode().rstrip()
        lista = ser_bytes.split("!")
        ser.reset_input_buffer()  
        print(lista)
    
    except:
        print("mi sto connettendo")
        ser.reset_input_buffer()  
    else:
        global oldlista

        try:
            
            if len(lista) >1: ##and lista != oldlista :
                oldlista = lista.copy()
                
                
                x_vals.append(next(index))
                y_vals.append(float(lista[0]))
                another_vals.append(float(lista[1]))
                
                plt.cla() #elimina le altre righe, in questo modo ha sempre lo stesso colore  
                plt.plot(x_vals,y_vals, label ='no filtro')
                plt.plot(x_vals,another_vals, label ='filtro')

                plt.legend(loc='upper left')
                plt.tight_layout()
        except: pass

    








  



    
ani = FuncAnimation(plt.gcf(), animate, interval=100)
plt.tight_layout()
plt.show()
    
 