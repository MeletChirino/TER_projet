"""Views file for django"""
import os
from pathlib import Path
from django.shortcuts import render, redirect
#serial functions
from .serial_ports import serial_ports
from .temoin import Temoin
#matplotlib
import matplotlib.pyplot as plt
import numpy as np

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
        data = arduino.get_data()
        print("data =  ")
        lap = 0
        t1 = []
        t2 = []
        t3 = []
        times = []
        relay_state = []
        for data_raw in data:
            try:
                splitted_data = str(data_raw).split("/")
                print(splitted_data)
                #import pdb; pdb.set_trace()
                t1_ = float(splitted_data[1])
                t3_ = float(splitted_data[3])

                t1.append(t1_)
                t2.append(float(splitted_data[2]))
                t3.append(t3_)
                times.append(t1_)
                times.append(t3_)
                relay_state.append(int(float(splitted_data[4])))
                print(F"Lap {lap}\nt1 = {t1[lap]}, t2 = {t2[lap]}, t3 = {t3[lap]}, relay_ok = {relay_state[lap]}")
                lap += 1
            except Exception as err:
                print(F"error aleatorio guinho ginho: {err}")
        distance = []
        for i in range(1,6):
            d1 = int(request.POST[F'distance{i}'])
            d2 = d1 + int(request.POST[F'distancet'])
            distance.append(d1)
            distance.append(d2)
        print(F'distance\nLen = {len(distance)}')
        distance = np.array(distance)
        print(distance)
        times_lapse = []
        times = np.array(times)/1000
        for i, time in enumerate(times):
            if i == 0:
                times_lapse.append(time)
            else:
                new_time = time - times[i-1]
                times_lapse.append(new_time)

        print(F'times\nLen = {len(times_lapse)}')
        print(times)

        speed = distance / times_lapse
        print(speed)

        #plotting script
        fig, ax = plt.subplots()
        ax.plot(times, speed)
        ax.grid()
        img_path = os.path.join(BASE_DIR, 'static/img/graph.png')
        print(img_path)
        fig.savefig(img_path)

        relay = range(1,6)

        print(F'relay\nLen = {len(relay)}')
        relay = np.array(relay)
        print(relay)

        print(F'state\nLen = {len(relay_state)}')
        print(relay_state)

        fig, ax = plt.subplots()
        ax.stem(relay, relay_state)
        img_path = os.path.join(BASE_DIR, 'static/img/graph2.png')
        fig.savefig(img_path)
        #plt.show()


        data = {
                'img': img_path,
                'speed': speed.tolist(),
                'mean_speed': distance[-1]/times[-1],
                'state': relay_state,

                }
        #return render(request, 'index.html', context={'img': img_path})
        return render(request, 'index.html', context=data)
    else:
        pass
