import time
import serial
import serial.tools.list_ports 

ports = serial.tools.list_ports.comports()
for port, desc, hwid in sorted(ports):
	print("{}: {} [{}]".format(port, desc, hwid))

ser = serial.Serial("COM3", baudrate = 115200)
print("COM3 connected")
#ser.write(b'g')
while 1:
	serial_line = ser.readline()
	print(serial_line)

