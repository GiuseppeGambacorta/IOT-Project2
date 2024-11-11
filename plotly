#!/usr/bin/python
import serial
import serial.tools.list_ports as p

import plotly.graph_objects as go
import plotly.subplots as sp

ports = p.comports()
port=[]
for i in ports:
    port.append(i.device)

ser = serial.Serial(port[0],9600,timeout=5)
ser.reset_input_buffer()  



fig = sp.make_subplots(rows=1, cols=1)
scatter = go.Scatter(x=[], y=[], mode='lines+markers', name='Random Data')
fig.add_trace(scatter)

fig.layout.xaxis.range = [0, 100]
fig.layout.yaxis.range = [0, 100]
fig.layout.title = 'Real-Time Scatter Plot'
fig.layout.xaxis.title = 'X Axis'
fig.layout.yaxis.title = 'Y Axis'
fig.layout.template = 'plotly_white'


x = 0

oldlista = []
while(True):
    try:   
        ser_bytes = ser.readline().decode().rstrip()
        lista = ser_bytes.split("!")
    except ValueError:
        print("mi sto connettendo")
        ser.reset_input_buffer()  
    else:
        
        if lista[0] and not oldlista == lista:
          
            y = float(lista[0])
            fig['data'][0]['x'] = list(fig['data'][0]['x']) + [x]
            fig['data'][0]['y'] = list(fig['data'][0]['y']) + [y]
            x+=1
            fig.update_layout()
            fig.write_html('realtime.html')
            oldlista = lista.copy()
            print(lista)



