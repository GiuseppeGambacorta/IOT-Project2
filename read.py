#!/usr/bin/python
import serial
import serial.tools.list_ports as p

import matplotlib.pyplot as plt

plt.ion()


ports = p.comports()

port=[]
for i in ports:
    port.append(i.device)


ser = serial.Serial(port[0],9600,timeout=5)
ser.flushInput()

ser_bytes = ser.readline().decode().rstrip()
while (ser_bytes != 1000):
 ser_bytes = ser.readline().decode().rstrip()
 lista = ser_bytes.split(".")
 
 

 print(lista)