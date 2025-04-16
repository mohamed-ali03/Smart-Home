# Mini Smart Home System

This project is a demonstration of a Mini Smart Home System designed for automation and security, implemented as part of the Mind Cloud 10th Generation Training at the Faculty of Engineering, Alexandria University.

## Project Overview

The Mini Smart Home system integrates various smart technologies to enhance home security and automation. It features face recognition for door control, automated responses based on sensor data (motion, temperature, and lighting), and real-time alerts. The system is powered by a microcontroller (ATmega) and is programmed in C, using Proteus for simulation.

### Key Features:
- **Face Recognition for Security**: Used for controlling door access.
- **Keypad Access**: You can also enter the home using a keypad, providing an additional layer of security.
- **Smart Sensors**: Motion, temperature, and lighting sensors for automating actions.
- **Automated Alerts**: Sends real-time alerts based on sensor data.
- **Microcontroller Integration**: The system is based on an ATmega microcontroller, programmed with C language.
- **Proteus Simulation**: The system has been simulated using Proteus to verify hardware and software integration.

## Project Components

- **Microcontroller**: ATmega (used for controlling sensors, actuators, and communication).
- **Sensors**:
  - Temperature Sensor (to monitor temperature).
  - Motion Sensor (PIR sensor for detecting movement).
  - Light Sensor (for automatic lighting control).
- **Actuators**:
  - Door Lock (controlled through face recognition).
  - LED (for indicating system status).
- **Software**:
  - Proteus (for simulation).
  - C Language (for programming the microcontroller).

## How to Use

### Hardware Setup:
1. Connect the sensors (motion, temperature, and light) to the microcontroller as per the circuit diagram.
2. Connect the actuators (door lock and LED) to the appropriate pins.
3. Power the system using the recommended voltage.

## Project Instructions

1. **Face Recognition**: The system will read input from the camera (if integrated) or from predefined images for recognizing faces and unlocking the door.
2. **Keypad Access**: The system allows users to enter the home using a keypad, which enhances security by requiring a PIN for access.
3. **Sensor Data Handling**: The system continuously reads the data from the motion, temperature, and light sensors to trigger actions such as sending alerts or turning on/off the light.
4. **Alert System**: If any abnormal sensor readings are detected, an alert will be generated and sent to the user.

## Contributors

- **Mohamed Ali Mohamed** - Microcontroller Interfacing & Hardware Circuit
- **Moustafa Essameldin Moustafa** - Computer Vision & Machine Learning
- **Mariam Ahmed Mohamed** - PCB Design
- **Nora Alaa El-Din Mahmoud** - PCB Design

## Acknowledgments

- Thanks to the Mind Cloud 10th Generation Training for providing the platform to showcase this project.
