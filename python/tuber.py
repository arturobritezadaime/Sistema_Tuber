#!/usr/bin/python
# -*- encoding: utf-8 -*-

########################################################################
#IMPORTS
########################################################################
import serial
import requests
import json
import urllib


########################################################################
#CONSTANTS
########################################################################
URL = 'https://projecttuber.herokuapp.com/api/test?%s'


########################################################################
#METHODS
######################################################################## 
""" Envía los datos recibidos por el puerto serie al servidor mediante 
	una petición GET
    @param data: diccionario de datos
    @type data: dict
"""
def send_data(data):
	
	queryString = urllib.urlencode(data) 
	url = URL % queryString
	request = requests.get(url)

	print
	print "URL: %s" % url
	print "Estado: %s" % "OK" if request.status_code else "ERROR"
	print "Respuesta: %s" % request.text
		

########################################################################
#PROGRAM
######################################################################## 

#configuramos el puerto serie
ino = serial.Serial()
ino.port = "/dev/ttyACM1"
ino.baudrate = 9600
ino.bytesize = serial.EIGHTBITS #number of bits per bytes
ino.parity = serial.PARITY_NONE #set parity check: no parity
ino.stopbits = serial.STOPBITS_ONE #number of stop bits
ino.timeout = 1            #non-block read
ino.xonxoff = False     #disable software flow control
ino.rtscts = False     #disable hardware (RTS/CTS) flow control
ino.dsrdtr = False       #disable hardware (DSR/DTR) flow control
ino.writeTimeout = 2     #timeout for write

#tratamos de abrir el puerto serie
try: 
    ino.open()
except Exception, e:
    print "Error open serial port: " + str(e)
    exit()


while True:

	try:
		data = json.loads(ino.readline())
		send_data(data)
	except:
		pass
