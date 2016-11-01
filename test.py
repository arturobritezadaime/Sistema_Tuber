# -*- codding: utf-8 -*-
import serial
import requests
#import time
port= serial.Serial("COM3",9600)
#time.sleep(1.8)
#port.write(b'k')

# 1ra secuencia no lee bien 
print(port.readline())
print(port.readline())
print(port.readline())
print(port.readline())
# 2da secuencia
print(port.readline())
print(port.readline())
print(port.readline())
print(port.readline())
# 3da secuencia
print(port.readline())
print(port.readline())
print(port.readline())
print(port.readline())

port.close()