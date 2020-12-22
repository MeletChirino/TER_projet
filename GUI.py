import kivy
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.lang import Builder
from kivy.properties import ObjectProperty
from kivy.uix.screenmanager import ScreenManager, Screen

class ConnectPage(Screen):
    text_input = ObjectProperty(None)

    def pressing(self):
        print("ke ricoolino", self.text_input.text)
        relay_app.root.current = "GetData"

class GetDataPage(Screen):
    def go_back(self):
        print("delicioso")
        relay_app.root.current = "ConnectPage"

class WindowManager(ScreenManager):
    pass

styles = Builder.load_file("styles.kv")

class RelayApp(App):
    def build(self):
        return styles

if __name__ == "__main__":
    relay_app = RelayApp()
    relay_app.run()
