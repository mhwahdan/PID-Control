# PID-Control project :-
A simple PID controlled motor using arduino uno micro-controller that's is connected serially with a django server in which users can access and control this motor from 
any where across the internet.this project was made for a project in an automatic control systems course at AASTMT university

# what is PID control :-
A proportional–integral–derivative controller (PID controller or three-term controller) is a control loop mechanism employing feedback that is widely used in industrial
control systems and a variety of other applications requiring continuously modulated control. A PID controller continuously calculates an error value e(t) as the difference 
between a desired setpoint (SP) and a measured process variable (PV) and applies a correction based on proportional, integral, and derivative terms 
(denoted P, I, and D respectively), hence the name.

<p align="center">
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/4/43/PID_en.svg/400px-PID_en.svg.png">
</p>

# practically speeking :-
In practical terms, PID automatically applies an accurate and responsive correction to a control function. An everyday example is the cruise control on a car, 
where ascending a hill would lower speed if constant engine power were applied. The controller's PID algorithm restores the measured speed to the desired speed with minimal
delay and overshoot by increasing the power output of the engine in a controlled manner.

<p align="center">
<img src="https://www.innovyze.com/media/5596/emagin-thouheed-diagram-3.png?width=463&height=339&mode=max">
</p>

# theory of operation :-
<p align="center">
<img src="https://www.tronicszone.com/tronicszone/wp-content/uploads/2020/03/closed-loop-control-system.png">
</p>

  - when the system runs it's given a setpoint where the output wants to reach the steady state at with minimum rise time, settling time and overshoot.
  - the error is calculated by subtracting the setpoint and the actual output.
  - the error integral and derivative are then calculated
  - the 3 values are then substituted with the system tuning paramters:
    - kp : prportional gain.
    - ki : integral gain.
    - kd : derivative gain.
    <p align="center">
    <img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/cd581e5c8539ce46453574d1188bd9d52a610fe0">
    </p>

  - the next input is now given to the plant making the system now a closed loop system with customizable and adaptive response
  
  

<p align="center">
<img src="https://engineerscommunity.com/uploads/db4532/original/1X/25d978ea3ebc8bd31dd267d9a663a0807d2c85d7.png">
</p>

# effect of each tuning parameter on the system :-

<p align="center">
<img src="https://upload.wikimedia.org/wikipedia/commons/3/33/PID_Compensation_Animated.gif">
</p>


# limitations :-
While PID controllers are applicable to many control problems, and often perform satisfactorily without any improvements or only coarse tuning, they can perform poorly 
in some applications and do not in general provide optimal control. The fundamental difficulty with PID control is that it is a feedback control system, with constant 
parameters, and no direct knowledge of the process, and thus overall performance is reactive and a compromise. While PID control is the best controller in an observer 
without a model of the process, better performance can be obtained by overtly modeling the actor of the process without resorting to an observer.
PID controllers, when used alone, can give poor performance when the PID loop gains must be reduced so that the control system does not overshoot, oscillate or hunt about
the control setpoint value. They also have difficulties in the presence of non-linearities, may trade-off regulation versus response time, do not react to changing process 
behavior (say, the process changes after it has warmed up), and have lag in responding to large disturbances.The most significant improvement is to incorporate feed-forward
control with knowledge about the system, and using the PID only to control error. Alternatively, PIDs can be modified in more minor ways, such as by changing the parameters
(either gain scheduling in different use cases or adaptively modifying them based on performance), improving measurement (higher sampling rate, precision, and accuracy, 
and low-pass filtering if necessary), or cascading multiple PID controllers.

# PID tuning :-
from the above we conculded that there are many limitations to the PID algorithm but some improvements can be made in order to enhance the algorithm performance.one of the methods
is tuninig the tuning parameters themselves in order to enhance the system output by

- decreasing rise time
- decresing settling time.
- decreasing overshoot and steady state error.

<p align="center">
<img src="https://www.allaboutcircuits.com/uploads/articles/IA_PID_controller_Table_1.jpg">
</p>


# what did we make :-
the project consists of a DC motor connected to an arduino microcontroller throught a h298n H-bridge with a hall-sensor attached to the motor shaft as an encoder to provide
feed back to the micro-controller. the micro-controller is connected to a PC throught a serial USB cable. this PC will act as a server where the clients can send control commands
throught the server's user interface in order to provide a user-friendly and abstract method for communication with the micro-controller from any location throughtout the internet.

# hardware used :-

- arduino UNO.
<p align="center">
<img src="https://m.media-amazon.com/images/I/51Kf4mBBeRL._AC_SY350_.jpg">
</p>
- l298n H-bridge.
<p align="center">
<img src="https://sc04.alicdn.com/kf/HTB11Y_LazvuK1Rjy0Faq6x2aVXa8.jpg">
</p>
- JGA25-370-CE DC motor with 12 volts power supply.
<p align="center">
<img src="https://m.media-amazon.com/images/I/417oaJdOSxL._AC_SX679_.jpg">
</p>
- PC that acts as a server.

<p align="center">
<img src="https://www.ubuy.com.eg/productimg/?image=aHR0cHM6Ly9tLm1lZGlhLWFtYXpvbi5jb20vaW1hZ2VzL0kvNzFZc0Y1c2VQNkwuX0FDX1NMMTUwMF8uanBn.jpg">
</p>

# what is Django?
Django is a Python-based free and open-source web framework that follows the model–template–views (MTV) architectural pattern. It is maintained by the Django Software Foundation (DSF), an independent organization established in the US as a 501(c)(3) non-profit.

<p align="center">
<img src="https://repository-images.githubusercontent.com/253698085/cce90300-78c3-11ea-8b94-604fad2c516d">
</p>


# how the program works :-
- the user enters the system paramters from the gui and click start motor.
<p align="center">
<img src="https://github.com/mhwahdan/PID-Control/blob/main/UI.png">
</p>

# what is next :-

- create a simulation for the motor using simulink.
- train an AI model that can predict the system tuning parameters of that particular motor given the setpoint.
- use the trained model to fine tune the system tuning paramters given the setpoint only to remove the neccesity of maually inserting the tuning paramters.
