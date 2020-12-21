import kivy
from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.gridlayout import GridLayout
from kivy.uix.textinput import TextInput

class MainPage(GridLayout):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.cols = 2

        self.add_widget(Label(text="Lista de seriales"))

        self.ip = TextInput(multiline=False)
        self.add_widget(self.ip)


class RelayApp(App):
    def build(self):
        return MainPage()

if __name__ == "__main__":
    RelayApp().run()
