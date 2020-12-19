from time import sleep
import serial

print("starting program")
temoin = serial.Serial('/dev/ttyACM0',115200, timeout=.1)
stop = "a"
input("pulsa enter")
temoin.write(b'start\n')
n = 0

while n<= 100:

    incomming_data = ""
    incomming_data = temoin.readline()

    print(incomming_data[:-2])

    print("message received")
    #sleep(1)#delay
    n+=1

print("\n\nfinish Program")
temoin.write(b'start\n')
temoin.close()
exit()
