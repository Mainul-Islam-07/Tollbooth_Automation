#  🚧 Tollbooth_Automation
## ℹ️ Overview
Developed an automated tollbooth system capable of managing vehicle access efficiently, securely, and intelligently using a state machine–based control architecture.
The core logic is modeled as a finite state machine, enabling the system to transition between different operational modes depending on real-time triggers like camera input, payment status, vehicle movement, or override commands.
## 🌟 Highlights

### Microcontroller 💻
STM32F103C8t6 is used as the microcontroller.

### Ethernet Communication 🌐
Wiznet W5500 is used for Ethernet communication with the computer.

### UART Communication 🔄
Two UART communication interfaces (One of them is for debugging).

## ⚙️ Features 
### Vehicle Detection (Entry) 🚗
Detection of an approaching vehicle using inductive loop coils installed on the entry lane.

### Automated Boom Barrier Control 🚧
The boom barrier is raised or lowered based on toll payment status and vehicle position, ensuring only authorized passage.

### Vehicle Detection (Exit) 🚙
Detection of a car leaving the toll area is also handled via loop coils on the exit side.

### Car Exit Confirmation via IR Sensor 🌟
An IR sensor provides an additional check to confirm that the car has left the toll zone properly.

### Siren Control for Violations 🚨
A siren is triggered in case of illegal car passage (e.g., unpaid exit) and turned off after resolution or proper payment.

### TCU Breach Detection 🔒
The system monitors for unauthorized access or tampering with the Toll Controller Unit (TCU) and issues alerts on breach.

### Lane Operation Light Control 💡
The system manages lane indicator lights, guiding operators and drivers based on system state (e.g., red/green lights for status).

### Overhead Light Control 🌙
Overhead lighting at the booth is automatically controlled depending on operational mode or time of day.

### Additional Device Control (x3) ⚙️
Provision to control three additional AC or DC devices, configurable for future expansion (e.g., fan, display board, heater).

### PC Power Control (Upcoming) 💻
Planned feature to automatically turn the PC on/off based on toll activity or scheduled requirements. (Not yet implemented)

### Event Logging with External RTC (Upcoming) 🕰️
Future capability to log system events and state changes using a Real-Time Clock (RTC) module for time-stamped data. (Not yet implemented)


## Other Important aspects:

### Wiznet Interrupt-Based Communications 

### UART DMA Interrupt-Based Communication 

### Optocoupler-Based Input/Output for Isolation

### Encrypted Communication 🔐 (Not implemented yet)
 
## 🔁State Machine

<img src="https://github.com/user-attachments/assets/7cd5ac66-be35-46ad-b163-c8d257295584" width="450" />

## 🔧 Input/Output Circuit Diagram (Not Updated - Need Fix)

<img src="https://github.com/user-attachments/assets/903dff8d-692e-4b50-b9f8-ad7a57c612ae" alt="IO" width="450"/>

## PCB Sample Image

<img src="https://github.com/user-attachments/assets/6a1c5372-c8be-42e6-8a16-e3d0fdd3df82" alt="TCU" width="450"/>

## Proteus Simulation Sample (Not Updated - Need Fix)

<img src="https://github.com/user-attachments/assets/cbd41422-b215-4d06-ba9c-c9048b5bfddb" alt="abcde" width="450"/>


## ⬇️ Setup

Download and Install STM32CubeIDE from https://www.st.com/en/development-tools/stm32cubeide.html

Download and Install Hercules from https://www.hw-group.com/software/hercules-setup-utility

Download and Install Serial Debugger Assistant from https://apps.microsoft.com/detail/9nblggh43hdm?hl=en-US&gl=US

# PROBLEMS / SOLUTIONS / CONCERNS

1) Individual Flags for sensor update should be implemented in next iteration. 




