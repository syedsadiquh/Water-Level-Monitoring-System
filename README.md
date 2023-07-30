
![SCR-20230730-sfyz](https://github.com/syedsadiquh/Water-Level-Monitoring-System/assets/49514406/91192e4c-4238-427a-b0cd-b00c9be99557)# Water-Level-Monitoring-System
## Introduction 
This open-source Project will measure the water level in a tank and show its percentage using an HC-SR04 ultrasonic distance sensor. This project uses WE10 WiFi module to give this board WiFi Functionality to push the percentage data to a mqtt cloud.
This Project uses a RuggedBoard A5D2x, a SBC which is devloped by the Rugged Board Group and other components that are mentioned above.

## Hardware used and their Specifications
### RuggedBoard A5D2x 
It is an Open source Industrial single board computer powered by ARM Cortex-A5 SoC @500 MHz, implemented with the finest platform for rapid prototyping. RuggedBoard- A5D2x consists of Multiple Interfaces such as Ethernet, RS232, CAN, RS485, Digital Input and Digital Output with optically isolated, Standard MikroBus header for Add-On Sensors, Actuators and Multiple Wireless Modules such as ZigBee, LoRa, Bluetooth etc. mPCIe connector with USB interface used for Cloud Connectivity modules 3G, 4G, NB-IoT, WiFi. Expansion header with  GPIO, UART, I2C, SPI, PWR etc.
![94a05b_4055a3608de247708b14a526e7424f00~mv2](https://github.com/syedsadiquh/Water-Level-Monitoring-System/assets/49514406/d647a856-de55-4755-a00b-6897f3f889fa)

### WE10 WiFi Module
WE10 is a high performance, Wi-Fi 802.11 b/g/n module, targeted for applications where highly reliable wireless connection, High performance and ease of integration are the key requirements. WE10 is a highly integrated single chip 802.11 b/g/n WiFi module. WE10 has a 1T1R capable WLAN baseband, RF circuitary, built-in 2MB flash and a host for other peripherals. The module ships with either an on board high performance antenna or u.FL connector or just an RF port for the use to connect external antenna.

### HC-SR04 Ultrasonic Distance Sensor
The HC-SR04 Ultrasonic Distance Sensor is a sensor used for detecting the distance to an object using sonar. The HC-SR04 uses non-contact ultrasound sonar to measure the distance to an object, and consists of two ultrasonic transmitters (basically speakers), a receiver, and a control circuit. The transmitters emit a high frequency ultrasonic sound, which bounce off any nearby solid objects, and the reciever listens for any return echo. That echo is then processed by the control circuit to calculate the time difference between the signal being transmitted and received.
![download](https://github.com/syedsadiquh/Water-Level-Monitoring-System/assets/49514406/17329c2b-4197-453d-b2e9-f1b76cb75f1e)

## Prerequisites For Running the code
1. Have a x86_64-bit system running Ubuntu.
2. Flash the NOR for the Board. The NOR image is in the prerequisite folder of this repo. For help in flashing the fresh board, visit - https://developer.ruggedboard.com/g5-system-development-guide/flash-the-nor-using-tftp-for-rugged-board-a5d2x
3. Install Minicom on your host system.
4. Install Poky toolchain for cross-compiling for the RuggedBoard A5D2x. To install Poky-Toolchain, Visit - https://developer.ruggedboard.com/g5-system-development-guide/download-the-toolchain-for-rugged-board-a5d2x
5. At Last, Perform the host setup to configure the toolchain and enable host to board file transfer usign tftp. For steps, visit - https://developer.ruggedboard.com/g5-system-development-guide/host-setup

## How to run the code
1. Clone this repo and go to the code directory.
2. Make necessary changes in code, like changing the WiFi ssid, MQTT SERVER, CLIENT ID AND TOPICS to your MQTT Broker. 
3. Now, compile the code as shown in the host setup (last step) of the prerequisites section.
4. Once, the code is compiled without error. Transfer the executable to the RuggedBoard using tftp as shown in host setup (last step of prerequisite).
5. After the code is transfer to the board, Open Minicom on the serial port on which the board is connected (usually ttyUSB0)
6. On board, Navigate to /data/ directory, using <code>cd /data/</code>
7. Give all permissions to the executable using <code>chmod 777 distance</code>. Here, the executable name is "distance", replace it with yours.
8. Connect all components to the board as shown below:-<br>
![SCR-20230730-rklw](https://github.com/syedsadiquh/Water-Level-Monitoring-System/assets/49514406/f7ccb152-34db-44d2-9576-5745616f2ac6)

9. Now, run the executable on board using <code>./distance 100</code>. Here, I am giving the tank height as 100, you replace it with your desired tank height.

To check the data, open your MQTT Broker and see the data being updated as the water-level changes.

## Results
This project find the percentage of liquid left in tank and pushes it to the mqtt cloud. This project also notifies about if a new tank is required or not. It will show Tank full (when percentage is around 100%), Tank at 75 percent (at 75% Capacity), Tank at 50 percent (at 50% Capacity), Order New Tank (at 25% Capacity) and New Tank Req.(Urgent) at 0-5% capacity.
The percent is shown as ERROR when distance recorded by the sensor is more than the tank height.
![SCR-20230730-sfvt](https://github.com/syedsadiquh/Water-Level-Monitoring-System/assets/49514406/86011f04-f862-4371-9159-0f2f258e37f7)

![SCR-20230730-sfyz](https://github.com/syedsadiquh/Water-Level-Monitoring-System/assets/49514406/7e8451a7-4ea4-43c8-b0bf-ead67b6f3d90)

![SCR-20230730-sgbj](https://github.com/syedsadiquh/Water-Level-Monitoring-System/assets/49514406/a2b5ee73-0b07-4cb4-852b-30b68f585127)

<img width="873" alt="SCR-20230730-setf" src="https://github.com/syedsadiquh/Water-Level-Monitoring-System/assets/49514406/3844b68b-ea18-4e75-8182-50d32ae5a0b1">

Thank You for checking out my project!!!
