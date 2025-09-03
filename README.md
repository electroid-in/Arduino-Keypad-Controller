# Arduino-Keypad-Controller
This Arduino sketch interfaces with a custom keypad consisting of a 3x3 matrix     and 4 extra keys: '*', '0', '#', and 'R'. The extra keys are handled using     additional row pins. A status LED on pin 13 blinks whenever a key is detected. (keypad used in old telephone)
# Custom Arduino Keypad Controller

**Author:** Adhithyan S  
**Project Type:** Arduino  
**Device:** Custom Keypad (3x3 Matrix + Special Keys: `*`, `0`, `#`, `R`)  
**License:** MIT

---

## 📌 Description

This Arduino sketch interfaces with a **custom-built keypad** featuring:

- A 3x3 matrix of numeric keys (1–9)
- Extra row keys: `*`, `0`, `#`, and `R`
- LED feedback on keypress (pin 13)

---

## 🔌 Pin Mapping

| Function       	       | Keypad Pin   | Arduino Pin  |
|------------------------|--------------|--------------|
| Row 0        	       	 | 1            | D2           |
| Row 1               	 | 9            | D3           |
| Row 2                	 | 5            | D4           |
| Column 0      	       | 2            | D5           |
| Column 1            	 | 4            | D6           |
| Column 2       	       | 8            | D7           |
| Extra Row A (`*`, `0`) | 3 		        | D8           |
| Extra Row B (`#`)      | 6  	      	| D9           |
| Extra Row C (`R`)      | 7  		      | D10          |
| Status LED           	 | —            | D13          |

---

## 🔧 Special Key Logic

| Key | Trigger Pins                    |
|-----|---------------------------------|
| `*` | Row pin 3 (D8) + Col pin 2 (D5) |
| `0` | Row pin 3 (D8) + Col pin 4 (D6) |
| `#` | Row pin 6 (D9) + Col pin 8 (D7) |
| `R` | Row pin 7 (D10) + **Col pin 6 (D9)** ⬅️ NEW |

---

## ✅ Features

- Custom scanning for both matrix and extra-row keys
- Non-blocking input detection
- Serial monitor output
- Visual feedback via LED

---

## 🧾 License

MIT License © 2025 Adhithyan S
