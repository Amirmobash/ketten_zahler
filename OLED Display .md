# Visitor Counter with OLED Display and Relay

**Author:** AmirMobasheraghdam

This Arduino-based project counts the number of people entering and leaving a room and displays the current occupancy on an OLED screen. When at least one person is present, a relay is activated to turn on a light. The system uses two sensors (e.g., PIR or infrared break beams) to detect entry and exit events.

---

## Features

- Real‑time occupancy count displayed on a 0.96" OLED (SSD1306)
- Automatic light control via relay
- Separate counts for entries (`REIN`) and exits (`RAUS`)
- Simple and robust logic

---

## Hardware Components

| Component          | Quantity |
|--------------------|----------|
| Arduino (Uno/Nano) | 1        |
| OLED Display (SSD1306, 128x64, I²C) | 1 |
| Entry sensor (e.g., IR beam or PIR) | 1 |
| Exit sensor (e.g., IR beam or PIR) | 1 |
| Relay module       | 1        |
| Connecting wires   | as needed |

---

## Wiring Diagram

| Arduino Pin | Connected To          |
|-------------|-----------------------|
| 2           | Entry sensor (signal) |
| 3           | Exit sensor (signal)  |
| 5           | Relay module (IN)     |
| A4 (SDA)    | OLED SDA              |
| A5 (SCL)    | OLED SCL              |
| 5V          | OLED VCC, relay VCC   |
| GND         | OLED GND, relay GND, sensor GND |

**Note:**  
- Sensors are assumed to output **LOW** when triggered. If your sensors output **HIGH**, change the `if (inStatus == 0)` conditions accordingly.  
- The relay is active‑LOW (relay turns ON when pin 5 is LOW). If your relay is active‑HIGH, adjust the `digitalWrite(relay, ...)` lines.

---

## How It Works

1. The entry and exit sensors are continuously monitored.
2. When the entry sensor goes LOW, the `countin` variable is incremented.
3. When the exit sensor goes LOW, the `countout` variable is incremented.
4. The current occupancy (`now`) is calculated as:  
   `now = countin - countout`
5. If `now > 0` (someone is inside), the relay is activated (LOW) → light ON.
6. If `now <= 0` (room empty), the relay is deactivated (HIGH) → light OFF.
7. The OLED displays:
   - "Aktuelle Besucher" + the current number
   - Total entries (`REIN`) and exits (`RAUS`)
   - When the room is empty, a "Kein Besucher / Licht Aus" message is shown.

---

## Code Explanation (Key Parts)

- **Libraries:**  
  `Wire.h`, `Adafruit_GFX.h`, `Adafruit_SSD1306.h` – required for OLED communication and graphics.

- **Pin definitions:**  
  `inSensor` (pin 2), `outSensor` (pin 3), `relay` (pin 5).

- **Counters:**  
  `countin`, `countout` – total number of entry/exit events.  
  `in`, `out` – store the previous values for display.  
  `now` – current occupancy.

- **Logic:**  
  The sensors are read; if a sensor is LOW, the corresponding counter is incremented.  
  Because the loop runs very fast, a small delay (`delay(500)`) prevents multiple counts from a single trigger. For better debouncing, consider adding a short `delay(50)` after detecting a trigger or using an interrupt‑based approach.

---

## Installation & Usage

1. Install the required libraries via the Arduino Library Manager:
   - **Adafruit GFX Library**
   - **Adafruit SSD1306**
2. Connect the components as shown in the wiring diagram.
3. Upload the provided code to your Arduino board.
4. Power the system and test by triggering the sensors.

---

## Customization

- **Change sensor logic:** If your sensors output HIGH when triggered, replace `if (inStatus == 0)` with `if (inStatus == 1)`.
- **Change relay logic:** If your relay module is active‑HIGH, swap `HIGH` and `LOW` in the `digitalWrite(relay, ...)` calls.
- **Display messages:** Modify the text inside `display.print()` statements to your preferred language.

---

## License

This project is open‑source and free to use, modify, and distribute. Attribution to the original author is appreciated.

---

*Happy building!*  
AmirMobasheraghdam
