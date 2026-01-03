# hand-gesure-controlled-car
# Hand Gesture Controlled Car using Arduino

## Overview
This project demonstrates a hand gesture controlled robotic car using an Arduino-based embedded system. Hand gestures are captured using an MPU6050 sensor and transmitted wirelessly to control the movement of the car.

## Components Used
- Arduino Nano / UNO
- MPU6050 (Accelerometer + Gyroscope)
- nRF24L01 Wireless Module
- L298 Motor Driver
- DC Motors
- Power Supply

## Working Principle
Hand gestures are detected using the MPU6050 sensor. The sensor data is processed and classified using decision rules / ML logic, and corresponding movement commands are transmitted wirelessly to the car.

## Features
- Wireless gesture-based control
- Embedded decision logic / ML-based classification
- Modular and expandable design

## Applications
- Human–machine interaction
- Assistive robotics
- Embedded ML systems

## Future Improvements
- Replace rule-based logic with trained ML model
- Improve gesture accuracy
- Add obstacle avoidance

## Author
SP
## Note
This project is implemented by referring to an existing open-source example for nRF24L01-based motor control.
The code has been studied, tested, and is being incrementally modified for learning and enhancement purposes.

EEE | Embedded Systems | Machine Learning

Reference:
- Original concept/code inspired from: <[link](https://www.instructables.com/DIY-Hand-Gestures-Controlled-Car-Using-Arduino-NRf/)>
