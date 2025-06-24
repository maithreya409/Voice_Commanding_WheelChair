# Arduino Voice-Controlled Robot 🤖

A mobile robot controlled via Bluetooth voice commands with ultrasonic obstacle avoidance and buzzer alerts.

---

## 🔧 Features

- Bluetooth control (`FRONT`, `BACK`, `LEFT`, `RIGHT`, `STOP`)
- Ultrasonic sensing to detect obstacles (< 20 cm)
- Automatic stop and avoidance maneuvers with buzzer alert
- Dual DC motor control via L298N/L293D driver

---

## 📦 Components

| Component             | Description                              |
|----------------------|------------------------------------------|
| Arduino UNO          | Microcontroller board                    |
| HC‑05 Bluetooth      | Voice command receiver via `SoftwareSerial` |
| HC‑SR04 Ultrasonic   | Obstacle distance measuring              |
| L298N/L293D Driver   | Controls two DC motors                   |
| 2 × DC Gear Motors   | Drive the wheels                          |
| Buzzer               | Audible obstacle alert                   |
| Jumper wires, Breadboard | For connections                     |
| Battery pack         | Powers motors and Arduino               |

---

## 🔗 Connections

- **Motors → Driver**:  
  - IN1 → pin 6, IN2 → pin 7  
  - IN3 → pin 2, IN4 → pin 4  
  - ENA → pin 3 (PWM), ENB → pin 5 (PWM)

- **Ultrasonic**:  
  - TRIG → A0, ECHO → A1

- **Bluetooth (HC‑05)**:  
  - RX → Arduino A2, TX → Arduino A3 (`SoftwareSerial(2,3)`)

- **Buzzer**:  
  - + → A5, – → GND

---

## ⚙️ Installation & Usage

1. Clone the repo and open `.ino` in Arduino IDE.  
2. Connect hardware per the diagram above.  
3. Upload the sketch to your Arduino UNO.  
4. Reconnect Bluetooth pins **after** uploading.  
5. Pair with your phone (default PIN: `1234`).  
6. Use a voice-to-Bluetooth app to send commands like `FRONT` / `STOP`.  
   - If obstacle detected under 20 cm, robot stops, buzzes, and reverses or turns automatically.

---

## 💡 Customization

- Adjust motor speeds by changing `analogWrite(ena1/2, 200);`
- Set new obstacle threshold by changing `ULSensor < 20`
- Modify pin assignments to fit your wiring

---

## 🔄 How It Works

The main loop performs three tasks:

1. **Reads ultrasonic sensor** — stops and buzzes if an obstacle is too close.  
2. **Reads Bluetooth commands** (`FRONT`, `BACK`, etc.) and actuates motors.  
3. **Sends status updates** (`DISTANCE = X`) back via Bluetooth and Serial.  

Safety alerts and reversing behavior are handled in the `if (ULSensor < 20 && s > 0)` block.

---

## 📚 References & Inspiration

- Similar Bluetooth‑ultrasonic Arduino projects: HC‑05 voice‑controlled robots with obstacle avoidance :contentReference[oaicite:1]{index=1}  
- Circuit setups via Instructables and Hackster using HC‑05 and HC‑SR04 :contentReference[oaicite:2]{index=2}

---

## 🚀 Next Steps

- Add servo (SG90) to rotate the ultrasonic sensor for smarter navigation  
- Integrate offline voice modules like DF2301Q :contentReference[oaicite:3]{index=3}  
- Build a custom Android app for more robust command parsing

---

## 📄 License

This project is released under the **MIT License** — see `LICENSE.md` for details.
