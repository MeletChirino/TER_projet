import serial
from time import sleep

class Temoin():
    def __init__(self, serial_port, baud_rate, *args, **kwargs):
        self.serial_port = serial_port
        self.baud_rate = baud_rate
        self.connected = False

    def connect(self):
        print("starting program")
        try:
            self.temoin = serial.Serial(self.serial_port, self.baud_rate, timeout=.1)
        except Exception as E:
            print(E)
        sleep(3)

        attemps = 0;

        while not self.connected:
            print("preguntando si esta ahi")
            self.temoin.write(b'ok?\n')
            #incomming_data = self.read_data()
            incomming_data = self.read_data(mode = 1)
            print(incomming_data)
            if(incomming_data == b'ok'):
                print("respuesta favorable")
                self.connected = True
            else:
                print("respuesta desfavorable")
                self.connected = False
                attemps += 1
                sleep(1)
                if attemps >= 4:
                    raise("Maximo intento de conexion fallidos")
                    self.connected = True

    def read_data(self, mode, *args, **kwargs):
        incomming_data = ""
        byte_value = b""
        if(mode == None or mode == 1):
            while not incomming_data == b"\n":
                incomming_data = self.temoin.read()

                if(not (incomming_data == b"\n"
                    or incomming_data == b"\r")):

                    byte_value += incomming_data
            return byte_value
        elif(mode == 2):
            result = {'angle':1}

            while not incomming_data == b"/":
                incomming_data = self.temoin.read()
                if(not incomming_data == b"/"):
                    byte_value += incomming_data

            result['angle'] = float(byte_value)

            byte_value = b""

            while not incomming_data == b"\r":
                incomming_data = self.temoin.read()

                if(not (incomming_data == b"\n"
                    or incomming_data == b"\r")):

                    byte_value += incomming_data

            result['time'] = float(byte_value)

            return result

    def get_data(self):
        self.temoin.write(b'start\n')
        self.data = []
        total_data = 100
        n = 0

        while n <= total_data:
            print(str((n/total_data)*100)+"%")
            self.data.append(self.read_data(mode=2))
            n+=1

        self.temoin.write(b'start\n')

        print(self.data)

    def close(self):
        self.connected = False
        self.temoin.close()

if __name__ == '__main__':
    try:
        arduino = Temoin(
                serial_port='/dev/ttyACM0',
                baud_rate=115200
                )
        print(arduino.connected)
        arduino.get_data()
        arduino.close()

    except Exception as E:
        #arduino.close()
        print(E)
