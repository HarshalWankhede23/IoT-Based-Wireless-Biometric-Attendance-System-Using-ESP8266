
# IoT-Based Wireless Biometric Attendance System Using ESP8266

## 📌 Project Overview

The **Wireless Biometric Attendance System** is an IoT-based project designed to automate student attendance using fingerprint authentication and wireless communication.

The system uses an ESP8266 NodeMCU microcontroller connected to a fingerprint sensor to identify students. Attendance records are transmitted wirelessly to another ESP8266 NodeMCU connected to a computer. A Python application processes the received data and automatically generates an Excel attendance report.

The project reduces manual attendance work, saves time, and minimizes proxy attendance.

## 🎯 Objectives

- Automate student attendance using fingerprint authentication.
- Establish wireless communication between two ESP8266 NodeMCU modules.
- Transfer attendance records using Wi-Fi.
- Process received attendance data using Python.
- Generate and maintain attendance reports in Excel format.

## ⚙️ Hardware Components

| Component | Purpose |
|---|---|
| ESP8266 NodeMCU (Transmitter) | Fingerprint processing and wireless transmission |
| ESP8266 NodeMCU (Receiver) | Receives attendance records |
| Fingerprint Sensor | Biometric identification |
| 16×2 LCD Display | Displays system status |
| I2C LCD Adapter | LCD communication |
| Push Button | Triggers attendance transmission |
| Computer/Laptop | Receives and stores attendance data |

## 💻 Software & Technologies

- **Arduino IDE** – Embedded programming and NodeMCU development.
- **Embedded C/C++** – Microcontroller programming.
- **Python 3** – Attendance data processing.
- **PySerial** – Serial communication between receiver NodeMCU and computer.
- **OpenPyXL** – Excel attendance report generation.
- **Wi-Fi / ESP-NOW** – Wireless communication between NodeMCU modules.

## 🔄 System Architecture

```text
       Fingerprint Sensor
               |
               |
        ESP8266 NodeMCU
          (Transmitter)
               |
         Attendance Data
               |
        Wireless Wi-Fi
               |
        ESP8266 NodeMCU
           (Receiver)
               |
          USB / UART
               |
         Computer / PC
               |
         Python Program
               |
        Data Processing
               |
        OpenPyXL Library
               |
         Excel Report
```

## 🚀 Working Principle

1. **Fingerprint Enrollment:** Student fingerprints are registered and stored in the fingerprint sensor.

2. **Fingerprint Authentication:** When a student places their finger on the sensor, the system compares it with previously registered fingerprints.

3. **Attendance Collection:** After successful identification, the corresponding student ID and attendance information are processed by the transmitter NodeMCU.

4. **Wireless Transmission:** When the teacher presses the push button, collected attendance records are transmitted wirelessly to the receiver NodeMCU.

5. **Data Reception:** The receiver NodeMCU sends the received data to the computer through serial communication.

6. **Python Processing:** A Python application reads and decodes the received student ID, attendance status, and subject code.

7. **Excel Report Generation:** The OpenPyXL library automatically stores attendance records in an Excel spreadsheet along with date and time.

## 📊 Attendance Data Format

The system uses a data frame containing three fields:

`[Student_ID, Attendance_Status, Subject_Code]`

Example:

`[1, 0, W]`

| Field | Description |
|---|---|
| 1 | Student ID |
| 0 | Absent |
| 1 | Present |
| W | Subject code |

Python processes this information and maps it to the corresponding student details and subject.

## ✨ Key Features

- Fingerprint-based student authentication.
- Wireless attendance data transmission.
- Two-node ESP8266 communication architecture.
- Automatic attendance collection.
- Python-based serial data processing.
- Automatic Excel attendance report generation.
- LCD-based system status display.

## 🔮 Future Enhancements

- Cloud-based attendance storage.
- Web dashboard for attendance monitoring.
- Real-time attendance analytics.
- Mobile application integration.
- Improved error handling and communication reliability.

## 📁 Project Structure

```text
Wireless-Biometric-Attendance-System/
│
├── Arduino_Code/
│   ├── Transmitter/
│   │   └── transmitter.ino
│   │
│   └── Receiver/
│       └── receiver.ino
│
├── Python_Code/
│   └── attendance.py
│
├── Output/
│   └── attendance.xlsx
│
├── Circuit_Diagram/
│
├── Images/
│
└── README.md
```

## 👨‍💻 Skills Demonstrated

- Embedded C/C++ Programming
- ESP8266 NodeMCU
- Arduino IDE
- IoT and Wireless Communication
- Fingerprint Authentication
- UART / Serial Communication
- Python Programming
- Hardware–Software Integration

## 📌 Project Domain

**Internet of Things (IoT) | Embedded Systems | Biometric Security | Wireless Communication**

---

**Developed as a Diploma Final-Year Project**  
Electronics and Telecommunication Engineering
