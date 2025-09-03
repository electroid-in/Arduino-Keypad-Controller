/*
  Keypad Controller - Custom 3x3 + Extra Keys (*, 0, #, R)
  Author: Adhithyan S
  GitHub: https://github.com/electroid-in/Arduino-Keypad-Controller/blob/main/KeypadController.ino

  Description:
    This Arduino sketch interfaces with a custom keypad consisting of a 3x3 matrix
    and 4 extra keys: '*', '0', '#', and 'R'. The extra keys are handled using
    additional row pins. A status LED on pin 13 blinks whenever a key is detected.

  Keypad Layout:

      [1] [2] [3]
      [4] [5] [6]
      [7] [8] [9]
      [*] [0] [#]
             [R]

  R KEY SPECIAL LOGIC:
    R is detected by connecting pin 6 (D9) and pin 7 (D10)
*/

// -------------------- Pin Definitions --------------------
const int KP_PIN_1 = 2;   // Row 0 → keypad pin 1
const int KP_PIN_9 = 3;   // Row 1 → keypad pin 9
const int KP_PIN_5 = 4;   // Row 2 → keypad pin 5

const int KP_PIN_2 = 5;   // Column 0 → keypad pin 2
const int KP_PIN_4 = 6;   // Column 1 → keypad pin 4
const int KP_PIN_8 = 7;   // Column 2 → keypad pin 8

const int KP_PIN_3 = 8;   // Extra Row A (*, 0) → keypad pin 3
const int KP_PIN_6 = 9;   // Extra Row B (#) and R col → keypad pin 6
const int KP_PIN_7 = 10;  // Extra Row C (R row) → keypad pin 7

const int LED_PIN = 13;

// -------------------- Matrix Key Setup --------------------
const int rowPins[3] = { KP_PIN_1, KP_PIN_9, KP_PIN_5 };
const int colPins[3] = { KP_PIN_2, KP_PIN_4, KP_PIN_8 };

// -------------------- Extra Keys Mapping --------------------
struct ExtraRow {
  int pin;
  char keys[3];  // Maps to col0, col1, col2
};

// * = pin3 + col0 (D5), 0 = pin3 + col1 (D6)
// # = pin6 + col2 (D7)
// R = pin7 + pin6 (D10 + D9)
ExtraRow extraRows[2] = {
  { KP_PIN_3, { '*', '0',  0  } },  // * and 0
  { KP_PIN_6, {  0 ,  0 , '#' } }   // #
};

// -------------------- Setup --------------------
void setup() {
  Serial.begin(9600);

  for (int r = 0; r < 3; r++) {
    pinMode(rowPins[r], OUTPUT);
    digitalWrite(rowPins[r], HIGH);
  }

  for (int c = 0; c < 3; c++) {
    pinMode(colPins[c], INPUT_PULLUP);
  }

  pinMode(KP_PIN_3, OUTPUT); digitalWrite(KP_PIN_3, HIGH);
  pinMode(KP_PIN_6, OUTPUT); digitalWrite(KP_PIN_6, HIGH);
  pinMode(KP_PIN_7, OUTPUT); digitalWrite(KP_PIN_7, HIGH);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.println("Keypad ready.");
}

// -------------------- Scan Matrix --------------------
char scanMatrix() {
  const char map3x3[3][3] = {
    { '1', '2', '3' },
    { '4', '5', '6' },
    { '7', '8', '9' }
  };

  for (int r = 0; r < 3; r++) {
    digitalWrite(rowPins[r], LOW);
    delayMicroseconds(200);

    for (int c = 0; c < 3; c++) {
      if (digitalRead(colPins[c]) == LOW) {
        digitalWrite(rowPins[r], HIGH);
        return map3x3[r][c];
      }
    }

    digitalWrite(rowPins[r], HIGH);
  }

  return 0;
}

// -------------------- Scan Extra Keys (*, 0, #) --------------------
char scanExtra() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(extraRows[i].pin, LOW);
    delayMicroseconds(200);

    for (int c = 0; c < 3; c++) {
      if (digitalRead(colPins[c]) == LOW) {
        digitalWrite(extraRows[i].pin, HIGH);
        char k = extraRows[i].keys[c];
        if (k) return k;
      }
    }

    digitalWrite(extraRows[i].pin, HIGH);
  }

  return 0;
}

// -------------------- Scan R Key (pin7 + pin6) --------------------
char scanRKey() {
  pinMode(KP_PIN_7, OUTPUT);
  digitalWrite(KP_PIN_7, LOW);

  pinMode(KP_PIN_6, INPUT_PULLUP);
  delayMicroseconds(200);

  if (digitalRead(KP_PIN_6) == LOW) {
    pinMode(KP_PIN_6, OUTPUT);
    digitalWrite(KP_PIN_6, HIGH);
    digitalWrite(KP_PIN_7, HIGH);
    return 'R';
  }

  pinMode(KP_PIN_6, OUTPUT);
  digitalWrite(KP_PIN_6, HIGH);
  digitalWrite(KP_PIN_7, HIGH);
  return 0;
}

// -------------------- Blink LED --------------------
void blink() {
  digitalWrite(LED_PIN, HIGH);
  delay(120);
  digitalWrite(LED_PIN, LOW);
}

// -------------------- Main Loop --------------------
void loop() {
  char key = scanMatrix();
  if (!key) key = scanExtra();
  if (!key) key = scanRKey();

  if (key) {
    Serial.print("Key Pressed: ");
    Serial.println(key);
    blink();
    delay(200);
  }
}

