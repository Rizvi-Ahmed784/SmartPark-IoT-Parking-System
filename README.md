# SmartPark – IoT-Based Smart Parking Management System

SmartPark is an **IoT-based smart parking management system** developed using an **ESP32 microcontroller, ultrasonic sensors, IR sensors, servo motor, LCD display, and the Blynk IoT platform**.

The main purpose of the system is to automatically monitor parking slot availability and control the entry gate based on the current parking status. Users can also check the availability of parking spaces remotely through the Blynk app before arriving at the parking area.

## Project Overview

In a conventional parking system, drivers often need to enter the parking area to find out whether a space is available. SmartPark addresses this problem by continuously monitoring individual parking slots and displaying their current status.

When a vehicle arrives at the entrance, the system checks whether any parking slot is available. If at least one slot is empty, the automatic gate opens and allows the vehicle to enter.

When a vehicle occupies a parking slot, the corresponding ultrasonic sensor detects the vehicle and the slot status changes from **EMPTY** to **FULL**.

If all parking slots are occupied, the system identifies the parking area as **FULL**. In this condition, the entry gate remains closed when another vehicle arrives.

The same parking information is also sent to the **Blynk IoT platform**, allowing users to remotely check the available parking spaces.

## Main Features

* **Automatic Entry Gate**

  * Detects an approaching vehicle using an IR sensor.
  * Opens the gate automatically when a parking space is available.
  * Keeps the gate closed when the parking area is full.

* **Smart Parking Slot Detection**

  * Each parking slot is monitored using an ultrasonic sensor.
  * Detects whether a slot is occupied or vacant.
  * Updates the slot status in real time.

* **Real-Time Parking Dashboard**

  * Displays the current status of individual parking slots.
  * Shows which slots are empty and which are occupied.
  * Displays the overall parking availability.

* **Parking Full Detection**

  * When all available slots are occupied, the system identifies the parking area as full.
  * A new vehicle cannot enter while the parking area is full.

* **Blynk IoT Monitoring**

  * Parking information is transmitted through Wi-Fi using the ESP32.
  * Users can check parking availability remotely from the Blynk app.
  * This allows users to check whether a parking space is available before arriving.

* **Automatic Gate Control**

  * A servo motor operates the parking gate according to the system status.

## System Workflow

```text
              Vehicle Arrives
                    │
                    ▼
            Entrance IR Sensor
                    │
                    ▼
          ESP32 Checks Availability
                    │
          ┌─────────┴─────────┐
          │                   │
     Space Available       Parking Full
          │                   │
          ▼                   ▼
      Gate Opens          Gate Remains Closed
          │
          ▼
      Vehicle Enters
          │
          ▼
   Ultrasonic Sensor Detects
       Occupied Slot
          │
          ▼
     Slot → FULL
          │
          ▼
 Dashboard + Blynk Updated
```

## Hardware Components

| Component          | Purpose                                        |
| ------------------ | ---------------------------------------------- |
| ESP32              | Main microcontroller and Wi-Fi communication   |
| Ultrasonic Sensors | Detect vehicle presence in parking slots       |
| IR Sensors         | Detect vehicle movement at the entry/exit      |
| Servo Motor        | Automatically controls the parking gate        |
| LCD Display        | Displays parking status and system information |
| Blynk IoT Platform | Provides remote monitoring through smartphone  |

## Technologies Used

* **ESP32**
* **Arduino IDE**
* **C/C++**
* **Blynk IoT**
* **Ultrasonic Sensors**
* **IR Sensors**
* **Servo Motor**
* **LCD Display**
* **Wi-Fi / IoT Communication**

## Remote Monitoring with Blynk

One of the main features of SmartPark is its connection with the **Blynk IoT platform**.

The ESP32 sends the current parking information through Wi-Fi to Blynk. Therefore, users do not have to physically reach the parking area just to check availability.

For example, the system can show:

```text
Slot 1 → EMPTY
Slot 2 → FULL
Slot 3 → EMPTY
Slot 4 → FULL
Slot 5 → EMPTY
Slot 6 → EMPTY

Available Slots → 4
```

When all slots are occupied:

```text
Parking Status → PARKING FULL
Available Slots → 0
```

This information can be viewed through the Blynk app.


## Future Improvements

The current system can be further extended with features such as:

* Camera-based vehicle detection
* Online parking reservation
* Automated payment integration
* Larger-scale parking management
* Historical parking data and analytics

These are considered **future improvements** and are not part of the current implementation.

## Conclusion

SmartPark demonstrates how **embedded systems and IoT technologies can be combined to create an automated parking management solution**.

By integrating real-time slot detection, automatic gate control, local status display, and remote Blynk monitoring, the system helps users identify parking availability more conveniently and prevents vehicles from entering when the parking area is full.

This project provided practical experience in **ESP32 programming, sensor integration, servo control, Wi-Fi communication, and IoT-based monitoring**.
