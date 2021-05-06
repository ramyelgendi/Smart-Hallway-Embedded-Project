## Authors:
* Eman Negm - 90070312
* Ramy ElGendi - 900170269
* Salma Wafa - 900170578

## Proposed Idea and Flow
SmartHallway is the future for smart buildings. Our project idea revolves around the need to save energy and electricity. Since hallway lights are an ever-lasting reason for energy loss, we have decided to solve this problem. The idea of the SmartHallway is a hallway that has detectors to be able to tell whether people are passing or not and where exactly they are. Based on that, it lights up an appropriate number of ceiling lights to help them see in the parts of the hallway they are passing through at any given moment in time. Otherwise, the lights are off. In order to spread awareness, there is also a screen in the hallway showing the amount of energy consumption, how many lights are on, and how much that costs. Also, the number of people in the hallway is constantly calculated and compared to the appropriate number according to the social-distancing restrictions. If the number of people exceeds that limit, a buzzer is turned on. 

Going into more detail, we have a long hallway with 8 LEDs acting as ceiling lights. When someone is passing, that is detected using IR emitter diodes (transmitters) and IR receiver modules (receivers) across each other along the hallway in between the ceiling lights. There are 8 pairs of those. When they detect someone passing in front of them, the ceiling light paired with the detector lights up. These detectors are detecting objects at a very high rate to quickly respond to changes regardless of the speed of the passers. The number of people in the hallway is calculated by the IR transmitters and receivers, too. This is done by incrementing the count when the first IR detector pair detect an object and decrementing when the last one does (indicating a person has exited the hallway). The keypad is used to take user inputs and the LCD displays used to display the pre-set values by the user and more information about energy consumption, cost, the number of hallway lights that are on, the limit of people in the hallway, and the current count, etc. The user-input variables to the system are the dimensions of the hallway, which are used to calculate the appropriate number of people (limit) according to COVID-19 restrictions, as well as other details to further tailor the hallway to the user specifications.

## Components
### Software
* STM32CubeMX
* Keil µVision

### Hardware
* STM32L432KC MicroController Unit

* 8x LEDs
* 1x Buzzer
* 8x PIR Sensors
* 4x 1K Ohm Resistors
* 16x2 LCD Display
* 4x4 Keypad
* Potentiometer

## System Architecture

![System-Architecture](https://imgur.com/a1B95ey.png)

### PIR Sensors:
The passive infrared sensor (PIR sensor) is responsible for detecting any motion detection. Whenever any object passes by it, it sends a signal to the microcontroller that a moving object was detected. It is active high, which means that the output signal is low unless there is motion. In this setup, each PIR sensor has a corresponding LED. When a person moves, the PIR sensor produces an output signal and therefore action is taken by the MCU to produce the corresponding output signals to turn on the specified number of LEDs ahead of the moving person in the hallway. The LEDs are then turned off after a fixed amount of time after the person passes them.


### Microcontrollers:
In this project, we will use two STM32 Nucleo boards because the number of pins needed exceeds the output pins available in one board. To begin with, there are 8 output pins for each LED to light up the hallway. Also, there are 8 pins for the 4x4 keypad used by the user to initialize the project settings. There are also 8 input pins reserved for each photodiode. Also, there are pins to be used for the UART protocols. Therefore, one microcontroller will be responsible for taking the user input and the LCD, and the other board will be connected to the LEDs and the photodiodes. 


### UART:
The Universal Asynchronous Receiver/Transmitter protocol (UART) is used to communicate between the two microcontrollers. The board connected to the keypad will transform the user input to the other board. Also, the information regarding the energy consumption and its costs is sent to the board connected to the LCD.

General flow:
Each computer is connected to an STM32 L432KC MCU using UART2. The first one is connected to the circuit with the PIR sensors, LEDs, etc. (the hallway model), and the other to the LCD and the keypad (and its resistors). Both MCUs communicate together using UART. The user inputs the initial specifications which are received by the microcontroller connected directly to the keypad then transmits it to the other microcontroller to apply it to the LEDs. Whenever any interrupts occur to the system (people pass by), the second microcontroller detects the change and produces the corresponding output to this interrupt. It also transmits the needed information to the other board which is connected directly to the LCD, to display the updated costs and energy consumption. 

## Circuit Design

![Circuit-Design](https://imgur.com/pCw1dcv)

### Key:
- Orange: 8x IR Emitter Diode (Transmitter)
- Blue: 8x IR Receiver Module
- Red: Buzzer
### Description:
The circuit diagram is separated into 2 parts. The first part is the hallway part and the second part is the control part. In the first part, the hallway part, we will be using a microcontroller of type STM32 L432KC. This part will be responsible for detecting whether someone passes between the I. R. emitter (orange) and receiver (blue). Whenever someone passes between them, the LED will turn on. A person is detected in front of the LED when the value detected continuously by the IR receiver is blocked. This is also used to measure the number of people in the hallway, which is then compared to the maximum number required for safe social distancing. If the number exceeds the maximum limit, the buzzer will be triggered.

In the second part, there is a keypad and LCD display. The keypad is used to take user inputs and the LCD displays used to display the pre-set values by the user and more information about energy consumption, cost, the number of hallway lights that are on, social distancing information, etc. Both microcontroller units communicate with each other, exchanging data and variables using UART.

## Thank you!
