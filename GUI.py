# kivy libraries
import kivy
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.lang import Builder
from kivy.properties import ObjectProperty
from kivy.uix.screenmanager import ScreenManager, Screen
# matplotlib
import matplotlib.pyplot as plt
# Own libraries
from python_interface.temoin import Temoin
from python_interface.serial_ports import serial_ports

class ConnectPage(Screen):
    """Page used for connecting to serial port"""
    serial_port = ObjectProperty(None)
    baud_rate = ObjectProperty(None)
    boton = ObjectProperty(None)

    def scan_serial_ports(self):
        """
        Method for finding available serial ports in system
        """
        print("Buscando Puertos Seriales")
        serial_list = serial_ports()
        self.serial_port.values = serial_list


    def pressing(self):
        """
        Method for connecting to Serial port
        """
        serial_port_ = self.serial_port.text
        baud_rate_ = self.baud_rate.text
        arduino.serial_port = serial_port_
        arduino.baud_rate = baud_rate_
        try:
            arduino.connect()
            if(arduino.connected):
                relay_app.root.current = "GetData"
            else:
                self.boton.text = "reconectar"
        except:
            self.boton.text = "reconectar"


class GetDataPage(Screen):
    def go_back(self):
        """
        Method for Getting data from Arduino
        """
        arduino.get_data()
        print(arduino.data)
        total = list(range(1, len(arduino.data)))
        data = []
        time = []
        for i in total:
            data.append(arduino.data[i]['AcZ'])
            time.append(arduino.data[i]['time'])

        fig, ax = plt.subplots()
        ax.plot(time, data)
        ax.grid()
        fig.savefig('graph.png')
        fig.show()

        #Con los datos aqui en python podemos hacer graficos y la vaina
        #relay_app.root.current = "ConnectPage"

class WindowManager(ScreenManager):
    pass

styles = Builder.load_file("styles.kv")

class RelayApp(App):
    def build(self):
        return styles

if __name__ == "__main__":
    arduino = Temoin(
            serial_port='',
            baud_rate=1
            )
    relay_app = RelayApp()
    relay_app.run()
