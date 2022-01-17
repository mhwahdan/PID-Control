from django.shortcuts import render
from django.http import HttpResponse
import serial
from time import sleep
# Create your views here.





def index(request):
    return render(request, 'PID/index.html')

arduino = None

def start_pid(request):
    global arduino
    mode = str(request.GET["mode"])
    setpoint = str(request.GET["setpoint"])
    kp = str(request.GET["kp"])
    ki = str(request.GET["ki"])
    kd = str(request.GET["kd"])
    sleep(1)
    arduino = None
    sleep(1)
    arduino = serial.Serial(port='COM4', baudrate=115200, timeout=1)
    sleep(1)
    arduino.flushInput()
    sleep(1)
    arduino.flushOutput()
    sleep(1)
    arduino.write(bytes(mode, 'utf-8'))
    sleep(1)

    data = arduino.readline()
    if data == b'Enter Setpoint\r\n':
        arduino.write(bytes(setpoint, 'utf-8'))
    sleep(1)

    data = arduino.readline()
    if data == b'Enter KP\r\n':
        arduino.write(bytes(kp, 'utf-8'))
    sleep(1)


    data = arduino.readline()
    if data == b'Enter KI\r\n':
        arduino.write(bytes(ki, 'utf-8'))
    sleep(1)

    data = arduino.readline()
    if data == b'Enter KD\r\n':
        arduino.write(bytes(kd, 'utf-8'))


    return HttpResponse('hello')


def get_point(request):

    try:
        sleep(0.5)
        point = str(arduino.readline().decode().strip('\r\n'))#Capture serial output as a decoded string
    except Exception as exp:
        point = '0'
    return HttpResponse(point)

