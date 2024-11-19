#!/usr/bin/python
import serial
import serial.tools.list_ports as p


ports = p.comports()
port=[]
for i in ports:
    port.append(i.device)

ser = serial.Serial(port[0],9600,timeout=5)
ser.reset_input_buffer()  


oldlista = []
while (True):
    try:   
        ser_bytes = ser.readline().decode().rstrip()
        lista = ser_bytes.split("!")
    except ValueError:
        print("mi sto connettendo")
        ser.reset_input_buffer()  
    else:
        
        if lista[0] and not oldlista == lista:
            oldlista = lista.copy()
            print(lista)
