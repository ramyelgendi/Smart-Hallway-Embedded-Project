# iStreet

## Authors:
* Eman Negm - 90070312
* Ramy ElGendi - 900170269
* Salma Wafa - 900170578

## Proposed Idea and Flow
iStreet is the future for smart cities. Our project idea revolves around the need to save energy and electricity. Since street lights are an ever-lasting reason for energy loss, we have decided to solve this problem. The idea of the iStreet is a street that has detectors to be able to tell whether it is the morning or night. If it is nighttime, it detects whether cars are passing or not and where exactly they are. Based on that, it lights up an appropriate number of street lights to help them drive in the parts of the street where they are at any given moment in time. Otherwise, the street lights are off. In order to spread awareness, there is also a big screen in the street showing the amount of energy consumption and how much that costs. The electricity department is able to control the percentage of light intensity at night time for street lights that cars are in front of and those without cars in front of. Also, the speed limit is set, since our system also acts as a radar to detect any speeding cars. 

Going into more detail, we have a long street with 8 LEDs on the side acting as street lights. When a car is passing, that is detected using IR emitter diodes (transmitters) and IR receiver modules (receivers) across each other along the street in between the street lights. There are 8 pairs of those. When they detect a car passing in front of them, the street light paired with the lights up with the maximum light intensity preset by the user. These detectors are detecting objects at a very high rate to quickly respond to changes regardless of the speed of the toy car used. The speed of any car is determined by recording the time that car passed in front of the first IR detection unit and the last one. Then, calculating the difference between them. Given that we know the distance between both of these points, we can calculate the speed. If it exceeds the speed limit, a LED flashes (after the second detection unit) simulating a camera that would take a picture of that car. Our system can deal with any number of cars and consists of one lane only, hence the cars come one after the other, in a queue sense. 

## Components
### Software
* STM32CubeMX
* Keil µVision

### Hardware
* STM32L432KC MicroController Unit

* 9x LEDs
* 8x IR Emitter Diode (Transmitter)
* 8x IR Receiver Module (Receiver)
* Resistors

* LCD Display
* 4x4 Keypad

## System Architecture

![System Architecture](https://i.imgur.com/ySsuPK8.png)

### IR Sensors:
The infrared(IR) sensor consists of two components: IR LED and a photodiode. IR LED is responsible for transmitting IR rays in all directions that are invisible to the human eye. The photodiode produces a signal whenever it detects infrared rays. It is active low, which means the output signal is high unless there are detected infrared rays. In this setup, each IR LED has a corresponding photodiode right across the street, which means that the photodiode always outputs a high signal. When a car moves, it blocks the infrared signals produced by the IR LED from the photodiode, which means that the photodiode produces an output signal and therefore action is taken by the MCU to produce the corresponding output signals to turn on the 3 LEDs ahead of the moving car in street. The LEDs are then turned off after a fixed amount of time after the vehicle passes them. This happens only when the whole system does not operate in an environment with low light intensity simulating the real-life street as the street lights only operate at night. 


### Microcontrollers:
In this project, we will use two STM32 Nucleo boards because the number of pins needed exceeds the output pins available in one board. To begin with, there are 8 output pins for each LED to light up the street. Also, there are 8 pins for the 4x4 keypad used by the user to initialize the project settings (e.g. minimum and maximum light intensity of the LEDs). There are also 8 input pins reserved for each photodiode. Also, there are pins to be used for the UART protocols. Therefore, one microcontroller will be responsible for taking the user input and the LCD, and the other board will be connected to the LEDs and the photodiodes. 


### UART:
The Universal Asynchronous Receiver/Transmitter protocol (UART) is used to communicate between the two microcontrollers. The board connected to the keypad will transform the user input (e.g. the minimum and maximum light intensity of the LEDs) to the other board. Also, the information regarding the energy consumption and its costs is sent to the board connected to the LCD.
General flow:
Each computer is connected to an STM32 L432KC MCU using UART2. The first one is connected to the circuit with the IR sensors, LEDs, resistors, etc. (the street model), and the other to the LCD and keypad (user interface). Both MCUs communicate together using UART. The user inputs the initial specifications which are received by the microcontroller connected directly to the keypad then transmits it to the other microcontroller to apply it to the LEDs. Whenever any interrupts occur to the system (cars pass by), the second microcontroller detects the change and produces the corresponding output to this interrupt. It also transmits the needed information to the other board which is connected directly to the LCD, to display the updated costs and energy consumption. 

## Circuit Design
![Circuit Design](https://i.imgur.com/4H4VYrq.png)

### Key:
Red: LED Transistors
Orange: 8x IR Emitter Diode (Transmitter)
Blue: 8x IR Receiver Module

The circuit diagram is separated into 2 parts. The first part is the street part and the second part is the control part. In the first part, the street part, we will be using a microcontroller of type STM32 L432KC. This part will be responsible for detecting whether an object passes between the I. R. emitter (orange) and receiver (blue). Whenever an object passes between them, the LED will increase its intensity to the maximum pre-set by the user (e.g. 95%). In that case, that first LED to detect the object and the two ones in front of it will light up to show the car driver the way ahead of it. The resistors are used to control the voltage across the components. The exact values of them depend on our tests and those available in the market. An object is detected in front of the LED when the value detected continuously by the I. R. receiver is blocked. This is also used to measure the speed of the vehicles, which is then compared to the speed limit i.e. acts as a radar.

In the second part, there is a keypad and LCD display. The keypad is used to take user inputs and the LCD displays used to display the pre-set values by the user and more information about energy consumption, cost, the number of street lights that are on, the speed limit, minimum and maximum light intensity, etc. Both microcontroller units communicate with each other, exchanging data and variables using UART.

### Presentation Video: 
https://youtu.be/s2tDVStk0zc

## Thank you!
