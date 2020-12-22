import kivy
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout
from kivy.uix.textinput import TextInput
from kivy.uix.button import Button
from kivy.uix.widget import Widget
from kivy.properties import ObjectProperty

class MyGrid(Widget):
    serial = ObjectProperty(None)

    def pressing(self):
        print("press ", self.serial.text)
        self.serial.text = ""


class MainPage(GridLayout):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.cols = 1

        self.data1 = GridLayout()
        self.data1.cols = 2

        self.data1.add_widget(Label(text="Lista de seriales"))

        self.name = TextInput(multiline=False)
        self.data1.add_widget(self.name)

        self.send_button = Button(
                text = "Enviar",
                font_size = 40
                )
        self.send_button.bind(
                on_press = self.send_button_pressed
                )

        self.add_widget(self.data1)
        self.add_widget(self.send_button)


    def send_button_pressed(self, instance):
        print("""
        Tu ausencia crea un vacio existencial en mi
        que no puede ser llenado con simple alcohol y
        drogas.\n
        """)
        serial = self.name.text
        print(serial)
        self.name.text = ""
        self.send_button.text = "Cargando..."

class RelayApp(App):
    def build(self):
        return MyGrid()

if __name__ == "__main__":
    RelayApp().run()
