from time import sleep
import serial

print("starting program")
temoin = serial.Serial('/dev/ttyACM0',115200, timeout=.1)
stop = "a"
input("pulsa enter")
temoin.write(b'start\n')
n = 0
data = []

while n<= 100:

    incomming_data = ""
    incomming_data = temoin.readline()
    #u = int.from_bytes(incomming_data[:-2], byteorder='big', signed=True)
    u = float(incomming_data[:-2])

    #print(str(u))
    data.append(u)

    n+=1

print("Datos en memoria = ")
for number in data:
    print(number)

print("\n\nfinish Program")
temoin.write(b'start\n')
temoin.close()
exit()
