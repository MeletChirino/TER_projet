"""Views file for django"""
import os
from pathlib import Path
from django.shortcuts import render, redirect
#serial functions
from .serial_ports import serial_ports
from .temoin import Temoin
#matplotlib
import matplotlib.pyplot as plt

def serial_list(request):
    serial_ports_list = serial_ports()
    print(serial_ports_list)
    list_ = {'serial_ports_list': serial_ports_list}

    return render(request, 'serial_list.html', context=list_)

def report_page(request):
    BASE_DIR = Path(__file__).resolve().parent.parent
    if request.method!="POST":
        return redirect('home')

    port = request.POST['port']
    try:
        arduino = Temoin(port, 115200)
        arduino.connect()
    except:
        return serial_list()
    if(arduino.connected):
        arduino.get_data()
        total = list(range(1, len(arduino.data)))
        print(total)
        data = []
        time = []
        for i in total:
            data.append(arduino.data[i]['AcZ'])
            time.append(arduino.data[i]['time'])
        fig, ax = plt.subplots()
        ax.plot(time, data)
        ax.grid()
        img_path = os.path.join(BASE_DIR, 'static/img/graph.png')
        print(img_path)
        fig.savefig(img_path)

        return render(request, 'index.html', context={'img': img_path})
    else:
        pass
