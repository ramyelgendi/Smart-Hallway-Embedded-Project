## Authors:
* Eman Negm - 90070312
* Ramy ElGendi - 900170269
* Salma Wafa - 900170578

## Proposed Idea and Flow
SmartHallway is the future for smart buildings. Our project idea revolves around the need to save energy and electricity. Since hallway lights are an ever-lasting reason for energy loss, we have decided to solve this problem. The idea of the SmartHallway is a hallway that has detectors to be able to tell whether people are passing or not and where exactly they are. Based on that, it lights up an appropriate number of ceiling lights to help them see in the parts of the hallway they are passing through at any given moment in time. Otherwise, the lights are off. In order to spread awareness, there is also a screen in the hallway showing the amount of energy consumption, how many lights are on, and how much that costs. Also, the number of people in the hallway is constantly calculated and compared to the appropriate number according to the social-distancing restrictions. If the number of people exceeds that limit, a buzzer is turned on. 

Going into more detail, we have a long hallway with 8 LEDs acting as ceiling lights. When someone is passing, that is detected using PIR sensor. There are 8 of those. When they detect someone passing in front of them, the ceiling light paired with the sensor lights up. These sensors are detecting objects at a very high rate to quickly respond to changes regardless of the speed of the passers. The number of people in the hallway is calculated by the sensors, too. This is done by incrementing the count when the first sensor detects an object and decrementing when the last one does (indicating a person has exited the hallway). The keypad is used to take user inputs and the LCD displays used to display the pre-set values by the user and more information about energy consumption, cost, the number of hallway lights that are on, the limit of people in the hallway, and the current count, etc. The user-input variables to the system are the dimensions of the hallway, which are used to calculate the appropriate number of people (limit) according to COVID-19 restrictions, as well as other details to further tailor the hallway to the user specifications.

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

![System-Architecture](https://i.imgur.com/W02nOae.png)

### PIR Sensors:
The passive infrared sensor (PIR sensor) is responsible for detecting any motion detection. Whenever any object passes by it, it sends a signal to the microcontroller that a moving object was detected. It is active high, which means that the output signal is low unless there is motion. In this setup, each PIR sensor has a corresponding LED. When a person moves, the PIR sensor produces an output signal and therefore action is taken by the MCU to produce the corresponding output signals to turn on the specified number of LEDs ahead of the moving person in the hallway. The LEDs are then turned off after a fixed amount of time after the person passes them.


### Microcontrollers:
In this project, we will use two STM32 Nucleo boards because the number of pins needed exceeds the output pins available in one board. To begin with, there are 8 output pins for each LED to light up the hallway. Also, there are 8 pins for the 4x4 keypad used by the user to initialize the project settings. There are also 8 input pins reserved for each photodiode. Also, there are pins to be used for the UART protocols. Therefore, one microcontroller will be responsible for taking the user input and the LCD, and the other board will be connected to the LEDs and the photodiodes. 


### UART:
The Universal Asynchronous Receiver/Transmitter protocol (UART) is used to communicate between the two microcontrollers. The board connected to the keypad will transform the user input to the other board. Also, the information regarding the energy consumption and its costs is sent to the board connected to the LCD.

General flow:
Each computer is connected to an STM32 L432KC MCU using UART2. The first one is connected to the circuit with the PIR sensors, LEDs, etc. (the hallway model), and the other to the LCD and the keypad (and its resistors). Both MCUs communicate together using UART. The user inputs the initial specifications which are received by the microcontroller connected directly to the keypad then transmits it to the other microcontroller to apply it to the LEDs. Whenever any interrupts occur to the system (people pass by), the second microcontroller detects the change and produces the corresponding output to this interrupt. It also transmits the needed information to the other board which is connected directly to the LCD, to display the updated costs and energy consumption. 

## Circuit Design

![Circuit-Design](https://i.imgur.com/Gbu8HSF.png)

### Key:
- Orange: 8x PIR Sensors
- Red: Buzzer

## Technical Challenges

### Solved:
* We were not able to use IR transmitters and receivers (needed a lens to direct the IR rays uniformly)
* We used instead the PIR sensor (motion detector) which had unfamiliar aspects that we needed to setup such as sensitivity and delay
* We used a 4x4 keypad which requires not so simple connections, so we developed a class for it to detect the GPIO pins connected to the rows and columns and outputs the corresponding key pressed in an array.

### Unsolved:
* UART connection between both microcontrollers
* LCD Display 

## Current Status:

So far, in the hallway unit, we have set up the first and last PIR sensors (2 out of 8). If they detect an object, their corresponding LEDs light up. Also, when the limit of number of people is received or exceeded, the buzzer is turned on. 

In the control unit, the keypad is used to enter the limit of number of people and the number of light bulbs to light up for an individual. The LCD is set up, however, it is not fully complete now. Instead, the user is prompted and is able to see the data inputted on TeraTerm.

## Demo Videos:

### Control unit: https://youtu.be/_R8E__G3rLY
### Hallway unit: https://drive.google.com/file/d/1LbL7LdtcYgN_8OKbb80ukJCqRX-63Dz0/view?usp=sharing

## Github repo:
https://github.com/ramyelgendi/ES-Project2

## Thank you!
