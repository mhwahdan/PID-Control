from django.shortcuts import render
from django.http import HttpResponse
import serial
from time import sleep
# Create your views here.

prev_angle = 0
mode = 0

def index(request):
    return render(request, 'PID/index.html')


def start_pid(request):
    global prev_angle
    mode = str(request.GET["mode"])
    setpoint = float(request.GET["setpoint"]) if float(request.GET["setpoint"]) <= 720 else 720.0
    setpoint = setpoint * -1
    tmp = setpoint

    if mode == '2':
        setpoint = setpoint - prev_angle
        prev_angle = tmp

    setpoint = str(setpoint)

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
    return HttpResponse('hello')


def reset_motor(request):
    global prev_angle
    angle = prev_angle * -1
    prev_angle = 0
    arduino = serial.Serial(port='COM4', baudrate=115200, timeout=1)
    sleep(1)
    arduino.flushInput()
    sleep(1)
    arduino.flushOutput()
    sleep(1)
    arduino.write(bytes('2', 'utf-8'))
    sleep(1)
    data = arduino.readline()
    if data == b'Enter Setpoint\r\n':
        arduino.write(bytes(str(angle), 'utf-8'))
    return HttpResponse(angle)
