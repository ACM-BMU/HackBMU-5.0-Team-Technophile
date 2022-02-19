# HackBMU-5.0-Team-Technophile
# Vehicle-Accident-Alarm-System (VAAS)
## Problem Statement -- Road Safety and How we can reduce the death due to road accidents and provide immediate checkups and operations by doctors using technology.

Real time gps location based alarming system tracking the road accident and providing medical assitance plus concern from near by police station.

## Overview
In case of a accident the device setup inside the car will be able to sense it and send a SOS signal via uploading the location of the accident to a cloud storage.
This cloud database will be continuously read by a client side application, which lists all the active SOS signals. When a nearby incident is found the concerned authorities that are monitoring the application can take action.

## The Device
The device will be based on Arduino Uno. The microcontroller will be responsible for sensing the crash with inputs from different sensors. And sending the SOS with the location of the incident.
### Components of the device
- Arduino Uno
- ADLX345 Accelerometer Sensor
- Neo 6m GPS Module
- ESP8266 Wifi-Module

## Working of the device
### Crash Detection
The occurrence of accident is detected using an accelerometer sensor (ADLX335) and the severity of the accident is checked using an algorithm coded in the microcontroller which is basically a pre-set threshold for the input from the sensor when it is crossed the distress signal sending part is triggered.
The vibrational sensor is placed in the front part of the vehicle near the crumble zone because the immediate impact and its suppression happen there. If the impulse is so high that it gets detected even after controlling, then an accident has surely occurred.
### Sending Distress Signal
After the detection of crash the Arduino recieves the co-ordinates of the location from a GPS Module(Neo 6m). And then having already established an internet connection with the help of ESP8266 wifi module, the location co-ordinates, g-force to understand the severity of crash, and the time of crash is uploaded to thingspeak cloud server.
### Monitoring The Distress Signals
An Android Application built with kotlin will monitor the distress signals. It downloads the data from thingspeak in form of JSON file and then displays the time of accident and the g-force in a recyclerview. When clicked on the accident tab it shows the location of that accident marked on a google map.

## Future Scope
The device can be further improved with additon of more sensors like fire sensors or cameras that can send the damage assesment with the distress call as well. Radio communication can also be established since internet connectivity is not always available and to further improve the connectivity radio signals can be relayed from the radio of other vehicles as well.
We are also looking to add Artificial Intelligence technology in identifying the most prone area in the city where the majority of accidents happen, using our database,and the last one we are planning to add our own backend to our app.

## Other use cases
Trigger in this project is the g-force but repalcing it with flame sensors it can also be used as a fire alarm where the fire brigade can instantly know the location of fire.

## Prototype
![Prototype](https://github.com/ACM-BMU/HackBMU-5.0-Team-Technophile/blob/main/Images/Images/Prototype%20Circuit%20.jpeg)

## Simulation 
![Simulation](https://github.com/ACM-BMU/HackBMU-5.0-Team-Technophile/blob/main/Images/Images/Simulation%202.png)

## Prtotype Video
![Video Link](https://drive.google.com/file/d/1aWFcwWN4AhG3tOHWKMFAedt1JUv7SVkR/view?usp=sharing)

## Simulation Video
![Simulation Link](https://drive.google.com/file/d/1gnplex6wNeQgiRva1q0G5fTqwWtrFc64/view?usp=sharing)
