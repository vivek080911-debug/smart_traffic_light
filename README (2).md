# 🚦 Smart Traffic Light Controller for School Zone

> **Course:** Microprocessors and Computer Architecture (MPCA)
> **Team 14:** Naveen Prasad M · Vivek D · Vilas

---

## 📌 Project Overview

This project implements an **Automated Traffic Management System** specifically designed for **School Zones**. Unlike traditional timer-based systems, this system uses **demand-based signaling** — it prioritizes pedestrian safety by using sensors to detect students and vehicles, triggering a safe crossing sequence **only when needed**.

---

## 🛠️ Hardware Architecture

The system is built on the **ATmega328P (Arduino Uno)** architecture, interfacing with various peripherals to create a responsive environment.

### Components Used

| Component | Part | Purpose |
|-----------|------|---------|
| Microcontroller | Arduino Uno (R3) | Core processing unit |
| Ultrasonic Sensor | HC-SR04 | Vehicle detection & distance measurement |
| IR Sensor | IR Obstacle Sensor | Pedestrian trigger |
| Indicators | 3× LEDs (Red, Yellow, Green) + 220Ω resistors | Traffic signal output |
| Power | USB 5V / 9V DC Battery | System power supply |

### Pin Mapping

| Component | Pin | Mode |
|-----------|-----|------|
| Red LED | 13 | Output |
| Yellow LED | 12 | Output |
| Green LED | 11 | Output |
| IR Sensor | 2 | Input (INT0) |
| Trig (Ultrasonic) | 9 | Output |
| Echo (Ultrasonic) | 10 | Input |

---

## 💻 Software Logic

The firmware implements a **State Machine with Hardware Interrupts** to ensure the system is always responsive to pedestrian requests.

```
┌─────────────────────────────────────────────────────────────────┐
│                        STATE MACHINE                            │
│                                                                 │
│   [DEFAULT] ──── Detection ────► [WARNING] ──► [SAFE CROSS]    │
│   GREEN ON       (IR / Ultrasonic  YELLOW ON    RED ON          │
│                   < 20cm)          3 seconds    16 seconds      │
│       ▲                                             │           │
│       └─────────────────── Reset ───────────────────┘           │
└─────────────────────────────────────────────────────────────────┘
```

### State Descriptions

1. **Default State** — System maintains a `GREEN` light; traffic flows normally.
2. **Detection** — If the Ultrasonic sensor reads `< 20 cm` **OR** the IR sensor is triggered:
   - An Interrupt Service Routine (ISR) sets a pedestrian-request flag.
3. **Transition Sequence:**
   - `GREEN` turns OFF → `YELLOW` turns ON *(3-second warning)*
   - `YELLOW` turns OFF → `RED` turns ON *(16-second safety window)*
4. **Reset** — System reverts to the Default State after the safety window.

---

## 🚀 Getting Started

### Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) (v1.8+ or v2.x)
- Arduino Uno (R3) board
- All hardware components listed above

### Setup & Upload

1. **Wire the hardware** as per the Pin Mapping table above.
2. **Open** the `mpca.c` file in the Arduino IDE.
3. **Select board:** `Tools → Board → Arduino Uno`
4. **Select port:** `Tools → Port → (your COM/tty port)`
5. **Upload** by clicking the ➡️ Upload button (or `Ctrl+U`).
6. **Open Serial Monitor** (`Ctrl+Shift+M`) at **9600 Baud** to view real-time distance data.

---

## 📁 Project Structure

```
smart-traffic-school-zone/
├── mpca.c              # Main firmware source file
├── README.md           # Project documentation
└── docs/
    └── circuit.png     # Circuit diagram (if available)
```

---

## 👥 Team Contributions

| Member | Role |
|--------|------|
| **Naveen Prasad M** | Hardware interfacing, circuit integrity, and component calibration |
| **Vivek D** | Firmware development, interrupt handling, and logic optimization |
| **Vilas** | System documentation, state-flow analysis, and report generation |

---

## 📄 License

This project was developed for academic purposes under the **MPCA course**. All rights reserved by Team 14.
