import kivy
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.lang import Builder
from kivy.properties import ObjectProperty
from kivy.uix.screenmanager import ScreenManager, Screen
from python_interface.temoin import Temoin

class ConnectPage(Screen):
    serial_port = ObjectProperty(None)
    baud_rate = ObjectProperty(None)
    boton = ObjectProperty(None)

    def pressing(self):
        print("ke ricoolino")
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
        print("delicioso")
        arduino.get_data()
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
