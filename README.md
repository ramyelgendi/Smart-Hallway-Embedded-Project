## Authors:
* [Eman Negm](https://github.com/emannegm9)
* [Ramy ElGendi](https://github.com/ramyelgendi)
* [Salma Wafa](https://github.com/salmawafa)

## Proposed Idea and Flow
SmartHallway is the future for smart buildings. Our project idea revolves around the need to save energy and electricity. Since hallway lights are an ever-lasting reason for energy loss, we have decided to solve this problem. The idea of the SmartHallway is a hallway that has detectors to be able to tell whether people are passing or not and where they are. Based on that, it lights up an appropriate number of ceiling lights to help them see in the parts of the hallway they are passing through at any given moment in time. Otherwise, the lights are off. The hallway is monitored through a web server that shows the amount of energy consumption, how many lights are on, and how much that costs. Also, the number of people in the hallway is constantly calculated and compared to the appropriate number according to the social-distancing restrictions. If the number of people exceeds that limit, a buzzer is turned on. 

## Components
### Software
* STM32CubeMX
* Keil µVision
* Arduino IDE

### Hardware
* 3x STM32L432KC MicroController Unit
* 3x LEDs
* 1x Buzzer
* 3x IR Sensors
* 4x 1K Ohm Resistors
* 4x4 Keypad
* 3x ESP WROOM-32 Chips

## How to build
- First, in arduino files run the "GetReceiverBoardMAC" code to get the server's Mac address then paste it in the sender's code (also in arduino), specifically in the following files: "ESP32Node" and "ESP32EntranceExit"

- Make sure to change all WiFi SSID and passwords in the code.
- Make sure you have keil and arduino installed (use added arduino libraries in Arduino folders)
- Run all of the arduino codes first, then connect to the STM using the connections shown in circuit diagram. 
- Start by entering number of people on keypad, then the system will all connect and work automatically

## System Architecture

![System-Architecture](https://i.imgur.com/Z7V5YnO.png)

Note: The connection between each ESP-32 and STM Nucleoboard is done over UART1 and TerraTerm is used for the user-interface on the right-most computer.

### PIR Sensors:
The passive infrared sensor (PIR sensor) is responsible for detecting any motion detection. Whenever any object passes by it, it sends a signal to the microcontroller that a moving object was detected. It is active high, which means that the output signal is low unless there is motion. In this setup, each PIR sensor has a corresponding LED. When a person moves, the PIR sensor produces an output signal and therefore action is taken by the MCU to produce the corresponding output signals to turn on the specified number of LEDs ahead of the moving person in the hallway. The LEDs are then turned off after a fixed amount of time after the person passes them.

Click [Here](https://cdn-learn.adafruit.com/downloads/pdf/pir-passive-infrared-proximity-motion-sensor.pdf) for Datasheet.

### ESP-32S NodeMCU:

The programmable chip is used to connect the nodes (which are the STM boards used on different computers) using Wifi. The Chip was programmed on Arduino IDE just to send and receive data. No computation was done on this board, they were all done on the STM32.

![ESP-32Chip](https://i.imgur.com/StXU5RU.jpg)

### IR Sensor

Infrared Sensor. Was used instead of PIR in the node responsible for counting how many people enter/exit because it has no delay. It is active low, when an obstacle is detected, the signal goes low.

![ESP-32Chip](https://ram-e-shop.com/wp-content/uploads/2018/09/kit_object_ir.jpg)

### Microcontrollers:
In this project, we will use two STM32 Nucleo boards because the number of pins needed exceeds the output pins available in one board. To begin with, there are 8 output pins for each LED to light up the hallway. Also, there are 8 pins for the 4x4 keypad used by the user to initialize the project settings. There are also 8 input pins reserved for each photodiode. Also, there are pins to be used for the UART protocols. Therefore, one microcontroller will be responsible for taking the user input and the LCD, and the other board will be connected to the LEDs and the photodiodes. 


### UART:
The Universal Asynchronous Receiver/Transmitter protocol (UART) is used to communicate between the two microcontrollers. The board connected to the keypad will transform the user input to the other board. Also, the information regarding the energy consumption and its costs is sent to the board connected to the LCD.

Going into more detail, we have three central nodes: the server node, the entrance/exit node and the lights node. The entrance/exit node is responsible for counting the number of passengers in the hallway. This node is repeated at the ends of the hallway. Another main node is the lights node. This node is responsible for lighting up the LEDs for the passenger(s). The main node is called the server node. This node receives the number of passengers from the entrance/exit node and the number of LEDs turned on from the lights node. This node is also responsible for taking the user input (the max number of passengers in the hallway) and for activating the buzzer when the number of passengers exceed the threshold entered according to COVID-19 restrictions. Each node is connected to an ESP chip and they are all connected to the same network so that data can be sent/received between the nodes. The ESP chips are programmed using Arduino IDE.

## Circuit Design

![Circuit-Design](https://i.imgur.com/ngX2gVb.png)

## Limitations

### Current:
* Delay between ESP32s
* PIR Sensor was used for the LEDs node but it stopped working at the last moments so we had to use IR sensors also on LED node. The code can be modified easily for PIR.
* We only found 3 ESP32 nodes, therefore, we tried to fit our code (specially in demo) to work with 3. That is why we built our code in a modular way so that if we need to add more LEDs, we will just upload the LEDs code and it will work. Same thing if we want to add another entrance/exit for the hallway, we will just replicate the EntranceExit Node.

### Solved:
* We were not able to use IR transmitters and receivers LEDs(needed a lens to direct the IR rays uniformly), is we used the IR Sensor Module
* We used the PIR sensor (motion detector) which had unfamiliar aspects that we needed to setup such as sensitivity and delay
* We used a 4x4 keypad which requires not so simple connections, so we developed a class for it to detect the GPIO pins connected to the rows and columns and outputs the corresponding key pressed in an array.
* We used ESP32 to send and receive via ESP-Now protocol, which works on WiFi.
* Our ESP32 chip had a bug that the code was not being uploaded to it. We fixed it by connecting a 10microF capacitor to the enable pin.

### Future Work:
* Fix delay between ESP32 sending and receiving
* Upload data on web server instead of displaying over terra-term
* Modify PIR code for LED node.

## Current Status:

- We finished the ESP32-S Server and client connections, and they are now working. The project is ready for demo.

## Demo Videos First Milestone:

-  Control unit: https://youtu.be/_R8E__G3rLY
-  Hallway unit: https://drive.google.com/file/d/1LbL7LdtcYgN_8OKbb80ukJCqRX-63Dz0/view?usp=sharing

## Demo Video Final Milestone:

-  https://www.youtube.com/watch?v=rQcFynyWk3U

## Github repo:
https://github.com/ramyelgendi/Smart-Hallway-Embedded-Project

## References:
https://randomnerdtutorials.com/esp32-esp-now-wi-fi-web-server/
https://circuits4you.com/2018/12/31/esp32-hardware-serial2-example/
https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/uart.html
https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf

## Thank you!
