from django.shortcuts import render
from django.http import HttpResponse
import serial
from time import sleep
# Create your views here.

prev_angle = 0
arduino = None
kp = 0
ki = 0
kd = 0
mode = 0

def index(request):
    return render(request, 'PID/index.html')


def start_pid(request):
    global prev_angle
    global kp
    global ki
    global kd
    mode = str(request.GET["mode"])
    setpoint = float(request.GET["setpoint"]) if float(request.GET["setpoint"]) <= 720 else 720.0
    setpoint = setpoint * -1
    tmp = setpoint
    kp = str(request.GET["kp"])
    ki = str(request.GET["ki"])
    kd = str(request.GET["kd"])

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
    sleep(1)

    data = arduino.readline()
    if data == b'Enter KP\r\n':
        arduino.write(bytes('6', 'utf-8'))
    sleep(0.5)

    data = arduino.readline()
    if data == b'Enter KI\r\n':
        arduino.write(bytes('0.6', 'utf-8'))
    sleep(1)

    data = arduino.readline()
    if data == b'Enter KD\r\n':
        arduino.write(bytes('1', 'utf-8'))
    return HttpResponse(angle)
