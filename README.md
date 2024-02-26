# Autonomous Parking Vehicle

This project involves using an Arduino UNO microcontroller to create a parking lot robot capable of autonomously navigating and parking in the nearest available spot. By combining line following, ultrasonic sensing, and a search algorithm, the robot identifies and parks in the nearest open parking space, validated through extensive testing.

# Parking Lot Layout
![parking_lot_layout](https://github.com/IJAMUL1/Automated-Factory-Guided-Vehicle/assets/60096099/896fe77e-4570-4bf2-bc5a-13d0423bf5ed)

# Robot Demo
![Untitled video - Made with Clipchamp (6)](https://github.com/IJAMUL1/Automated-Factory-Guided-Vehicle/assets/60096099/e307b82f-e207-4fdd-a5fa-0d75c333c798)

## Table of Contents

- [Introduction](#introduction)
- [Project Requirement](#project-requirements)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Setup Instructions](#setup-instructions)
- [Usage](#usage)
- [Contributing](#contributing)

## Introduction

In this project, we address the challenge of designing an autonomous parking system capable of navigating a predefined path within a parking lot, detecting available parking spaces, and efficiently maneuvering to park in the first available spot. Our solution involves the use of an Arduino-based robot equipped with sensors to detect intersections, objects obstructing parking spaces, and indicators for successful parking. This documentation provides a comprehensive overview of the project's objectives, problem statement, scenario description, task requirements, deliverables, and additional resources for implementation. Whether you're a student, hobbyist, or enthusiast interested in autonomous robotics or tackling real-world challenges with Arduino, this documentation serves as a valuable resource to understand, replicate, and contribute to our project.

## Project Requirements

- Line Following Robot: The robot must accurately follow the path marked by black tape within the parking lot.
- Intersection Indication: Indicate when traversing intersections using LEDs.
- Object Detection: Detect objects obstructing parking spaces using a single ultrasonic sensor. Provide indication of object detection through LEDs and LCD displays.
- Parking Functionality: Successfully park in the first available parking space detected.
- Display of Occupied Spaces: Display the number of occupied parking spaces encountered before parking using LCD displays.

## Hardware Requirements

The hardware components required for the project, include:
- Chassis and mechanical components
- Arduino Uno
- 2 x Continous Servo Motors
- Pulolo Reflecance Sensor
- 2 x Ultrasonic Sensors
- Parallax 2 X 16 Serial LCD With Piezo Speaker 
- Power supply
- Breadboard
- Wires
- Leds
- Etc.

## Software Requirements

Specify all the software dependencies needed to run the project, including but not limited to:
- Parallax Propeller Toolchain
- SimpleIDE or PropellerIDE for development
- Propeller C libraries (simpletools, servo, ping)
- Raspbian OS
- Python 3.9 installed on the Raspberry Pi
- Python Library (OpenCv, Numpy)
- RPi.GPIO library for controlling GPIO pins (RPi.GPIO)

## Setup Instructions
# Raspberry Pi Setup
- Connect the camera module to the Raspberry Pi.
- Install Python 3.x on the Raspberry Pi if not already installed.
- Install OpenCV and NumPy libraries for Python on the Raspberry Pi.
- Install the RPi.GPIO library for controlling GPIO pins.
- Clone or download the project repository to the Raspberry Pi.
- Connect the GPIO pins to external devices such as LEDs and motor drivers as per the circuit diagram provided.
- Adjust the circuit connections and GPIO pin configurations in the code based on your use case.

# Parallax Properller Setup
- Connect the Parallax Propeller microcontroller to your computer.
- Install the Parallax Propeller Toolchain and SimpleIDE or PropellerIDE.
- Clone or download the project repository to local device.
- Open the project in SimpleIDE or PropellerIDE.
- Compile and upload the properller code to the Parallax Propeller microcontroller.

# Integration
- Connect raspberry pi to properller based on pin connection in code files respectively. 

## Usage

Once the code is uploaded to the microcontroller and the hardware is assembled, follow these steps to use the robot:

- Power on the robot.
- The robot will perform initialization routines, including sensor calibration.
- Depending on the mode of operation, the robot will perform tasks such as line following, obstacle avoidance, or intersection handling.
- Monitor the status LEDs to understand the system's behavior.
- Refer to the code documentation for specific functionality and control options.

## Contributing

Include guidelines for contributing to the project, such as how to report bugs, submit patches, or suggest improvements. Mention any coding standards or conventions to follow.
