# 🛸 Arduino UAV Remote Control System

A simple, lightweight **wireless remote control link** for Arduino-based UAV / RC projects, built using the **NRF24L01** radio module. Two joysticks on the transmitter send flight-control style data (throttle, yaw, pitch, roll) to a receiver in real time.

---

## 📦 What's Inside

| File | Role | Description |
|------|------|-------------|
| `RF_Transmitter.ino` | 🎮 Ground Station | Reads 2 analog joysticks and transmits their values over RF |
| `RF_Reciever.ino` | 🚁 Onboard Receiver | Receives joystick data and prints it to Serial (ready to be mapped to motors/servos) |

---

## 🔧 Hardware Required

**For each side (Transmitter & Receiver), you'll need:**

- 1x Arduino board (Uno / Nano / Pro Mini, etc.)
- 1x NRF24L01 radio module (+ breakout adapter recommended for stable 3.3V power)

**Transmitter only:**
- 2x Analog joysticks (4 axes total: X1, Y1, X2, Y2)

---

## 🔌 Wiring

### NRF24L01 → Arduino (both boards)

| NRF24L01 Pin | Arduino Pin |
|--------------|-------------|
| VCC | 3.3V ⚠️ (NOT 5V) |
| GND | GND |
| CE | 9 |
| CSN | 10 |
| SCK | 13 |
| MOSI | 11 |
| MISO | 12 |

### Joysticks → Transmitter Arduino

| Joystick Axis | Arduino Pin |
|----------------|-------------|
| Joystick 1 - X | A3 |
| Joystick 1 - Y | A5 |
| Joystick 2 - X | A7 |
| Joystick 2 - Y | A6 |

> ⚠️ **Power tip:** The NRF24L01 is sensitive to power fluctuations. If you get unreliable connections, add a **10–100µF capacitor** across the module's VCC and GND, or use a breakout board with a built-in voltage regulator.

---

## 📚 Required Library

Install via Arduino IDE Library Manager:

```
RF24 by TMRh20
```
*(Sketch → Include Library → Manage Libraries → search "RF24")*

---

## 🚀 How It Works

1. **Transmitter** reads the 4 joystick axes (`x1, y1, x2, y2`), maps each from `0–1023` to `0–180` (servo-friendly range), and sends them as a packed struct over RF.
2. **Receiver** listens continuously, and once a packet arrives, prints the 4 values to the Serial Monitor — ready for you to plug into motor/ESC or servo control logic.

```
Transmitter                     Receiver
┌──────────────┐    2.4GHz     ┌──────────────┐
│  Joysticks    │ ─────────────▶│  NRF24L01    │
│  + NRF24L01   │                │  + Arduino   │──▶ Serial Monitor
└──────────────┘                └──────────────┘
```

---

## ⚙️ Setup Steps

1. Wire both boards as described above.
2. Open `RF_Transmitter.ino` and upload it to your **transmitter/ground station** Arduino.
3. Open `RF_Reciever.ino` and upload it to your **receiver/onboard** Arduino.
4. Open the **Serial Monitor** (9600 baud) on the receiver to confirm data is being received.
5. Move the joysticks — you should see `X1`, `Y1`, `X2`, `Y2` values update live! 🎉

---

## 🛠️ Customization Ideas

- 🔄 Replace the shared placeholder address `"xxxxx"` with a unique 5-character address if running multiple UAVs nearby, to avoid interference.
- 🎯 Feed the received `x1/y1/x2/y2` values into `Servo.write()` or ESC/motor control code to actually drive your UAV.
- 📶 Bump `RF24_PA_LOW` up to `RF24_PA_HIGH` for longer range (needs stronger power supply).
- 🧭 Add checksum/failsafe logic to handle signal loss gracefully (e.g., auto-throttle-cut if no packet received for X ms) — **highly recommended for real flight safety**.

---

## ⚠️ Safety Note

This is a **hobby control link**, not a certified flight-safety system. Before flying anything real:
- Test failsafe behavior (what happens when the signal drops?).
- Always test propeller-off first.
- Follow your local drone/UAV regulations.

---

## 📝 License

Free to use and modify for personal and educational projects. Fly safe! 🛩️
