
#read the Readme file for installing dependencies and libraries
# Raspberry pi 4 with Neo6m GPS Module

import serial
import time
import string
import pynmea2
import datetime

while True:
    port="/dev/ttyAMA0"
    ser=serial.Serial(port, baudrate=9600, timeout=0.5)
    dataout = pynmea2.NMEAStreamReader()
    newdata=ser.readline()

    if newdata[0:6] == "$GPRMC":
        newmsg=pynmea2.parse(newdata)
        lat=newmsg.latitude
        lng=newmsg.longitude
        gps = "Latitude=" + str(lat) + "\nLongitude=" + str(lng)
        print(gps)
        print datetime.datetime.now()
