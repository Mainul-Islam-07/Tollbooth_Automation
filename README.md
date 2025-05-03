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

# ICPS Header Connection between PCBs



# PCB PROBLEMS / SOLUTIONS / CONCERNS

2nd Iteration PCB is not finalized yet.

## TOLL CONTROLLER UNIT

1) SCLK And RST Connection from W5500 to MCU is manually swapped using wires. It should be fixed in next PCB design Iteration.
2) TX and RX connection from both UARTs is manually swapped using wires. The ususal way is UART TX > MCU TX and UART RX > MCU RX. To be fixed in the nextIteration.

<img src = "https://github.com/user-attachments/assets/da398707-2ad4-429b-a40c-ffc396205046" alt = "Issues" width="250"/>
<img src = "https://github.com/user-attachments/assets/3f15256b-2000-42d6-bc8a-3bb45e6680ed" alt= "Issues01" width="320"/>

3) Since less current flow at Input, 1k ohm resistors attached at all of the 4 inputs in replaced by wire (shorting). Now the optocoupler responses any voltage from 6V. To be fixed in next iteration.
4) Voltage divider resistors are changed from 22k and 33k to 470 and 1k ohm for all inputs. It provides proper input to the mcu pins. To be fixed in next iteration.

<img src = "https://github.com/user-attachments/assets/b5e3da6f-c96f-46ce-9648-941d9ffe55ad" alt = "Issues02" width = "330" />
<img src = "https://github.com/user-attachments/assets/ba246bc0-5c29-4a2b-8899-34c18a818689" alt = "Issues03" width = "250" />

5) All 470 ohm connected from MCU to Relay signal input side is manually shorted. This is done for proper signal sending. To be fixed in next iteration.
6) Voltage divider resistors are changed from 22k and 33k to 33k and 100k for All UART RX. To be fixed in the next iteration.
   
<img src = "https://github.com/user-attachments/assets/a45c5864-0ab3-4efb-b142-26692c93332d" alt = "Issues04" width = "250" />
<img src = "https://github.com/user-attachments/assets/067f82fc-a382-42a9-a5fb-f66cbc7cef8a" alt = "Issues05" width = "250" />

8) w5500 needs to be powered using a regulator from 5V to 3.3V. To be Fixed in next iteration.


## RELAY BOARD

1) The resistor after 470 ohm should not be used. It should be kept open. To be fixed in the next iteration.
2) A pullup of 10k is given from 12 volt to base of bc557 in such a way that it can be made 0V / 12V when needed. To be fixed in the next iteration.


<img src = "https://github.com/user-attachments/assets/d6837dff-edaf-43e1-b514-d727617b3e3b" alt = "Issues06" width = "250" />
<img src = "https://github.com/user-attachments/assets/303b8c14-813f-426c-9fda-c4752f0b59b1" alt = "Issues07" width = "250" />

3) Pulldown resistor is not given. Its not needed. To be fixed in the next iteration.

<img src = "https://github.com/user-attachments/assets/b360efda-562d-43aa-a4d3-4d545c14fb79" alt= "Issues08" height = "180"/>

## LED BOARD

1) 1k ohm is connected to every signal end of mosfet used for powering RGB LED. Otherwise biasing issues emerge. To be fixed in the next iteration.
   
<img src = "https://github.com/user-attachments/assets/e0832800-fdeb-43e0-9373-877852bd6c64" alt = "Issues09" width = "250" />



2) Led that are powered by mcu directly should be equiped with less value resistor, lets say 100ohm. Applicable for Camera_Trigger, Payment and Ping LEDs.


# CODE PROBLEMS / SOLUTIONS / CONCERNS

1) Individual Flags for sensor update should be implemented in next iteration. 




