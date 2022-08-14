#define MEMORY_PROGRAMMING_MODE A1
#define WRITE_TO_MEMORY A2
#define RESET_COMPUTER A3
#define START_STOP_CLOCK A0
#define MEMORY_ADDRESS_PIN_0 10
#define MEMORY_ADDRESS_PIN_1 11
#define MEMORY_ADDRESS_PIN_2 12
#define MEMORY_ADDRESS_PIN_3 13
#define MEMORY_PIN_0 2
#define MEMORY_PIN_1 3
#define MEMORY_PIN_2 4
#define MEMORY_PIN_3 5
#define MEMORY_PIN_4 6
#define MEMORY_PIN_5 7
#define MEMORY_PIN_6 8
#define MEMORY_PIN_7 9

const int MEMORY_ADDRESSES = 16;
const int MEMORY_ADDRESSES_PINS = 4;
const int MEMORY_PINS = 8;
const int LEDS = 14; // array for KITT supercar LEDs effect
const int PINS = 8;


/*
 * Fibonacci program.
 * References: - https://youtu.be/a73ZXDJtU48?t=263
 * Restart from scratch when Carry is set (calculation > 255)
 */
int FIBONACCI_PROGRAM_1[MEMORY_ADDRESSES /*4 digits*/][MEMORY_ADDRESSES_PINS /*4 digits*/+ MEMORY_PINS /*4 digits*/] = {
  { 0, 0, 0, 0,    0, 1, 1, 0,    0, 0, 0, 1 }, // $0   LDI #1
  { 0, 0, 0, 1,    0, 1, 0, 1,    1, 1, 1, 0 }, // $1   STA $14
  { 0, 0, 1, 0,    0, 1, 0, 1,    1, 1, 1, 1 }, // $2   STA $15
  { 0, 0, 1, 1,    0, 0, 0, 1,    1, 1, 1, 0 }, // $3   LDA $14
  { 0, 1, 0, 0,    0, 0, 1, 0,    1, 1, 1, 1 }, // $4   ADD $15
  { 0, 1, 0, 1,    0, 1, 1, 1,    0, 0, 0, 0 }, // $5   JC  $0
  { 0, 1, 1, 0,    1, 1, 1, 0,    1, 1, 1, 0 }, // $6   OUT
  { 0, 1, 1, 1,    0, 1, 0, 1,    1, 1, 0, 1 }, // $7   STA $13
  { 1, 0, 0, 0,    0, 0, 0, 1,    1, 1, 1, 1 }, // $8   LDA $15
  { 1, 0, 0, 1,    0, 1, 0, 1,    1, 1, 1, 0 }, // $9   STA $14
  { 1, 0, 1, 0,    0, 0, 0, 1,    1, 1, 0, 1 }, // $10  LDA $13
  { 1, 0, 1, 1,    0, 1, 0, 1,    1, 1, 1, 1 }, // $11  STA $15
  { 1, 1, 0, 0,    0, 1, 0, 0,    0, 0, 1, 1 }, // $12  JMP $3
  { 1, 1, 0, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // $13
  { 1, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 1 }, // $14
  { 1, 1, 1, 1,    0, 0, 0, 0,    0, 0, 0, 1 }, // $15
};

// Improved memory locations selection in order to ease understanding of what's going on
int FIBONACCI_PROGRAM_2[MEMORY_ADDRESSES /*4 digits*/][MEMORY_ADDRESSES_PINS /*4 digits*/ + MEMORY_PINS /*4 digits*/] = {
  { 0, 0, 0, 0,    0, 1, 1, 0,    0, 0, 0, 1 }, // $0   LDI #1
  { 0, 0, 0, 1,    0, 1, 0, 1,    1, 1, 0, 1 }, // $1   STA $13
  { 0, 0, 1, 0,    0, 1, 0, 1,    1, 1, 1, 0 }, // $2   STA $14
  { 0, 0, 1, 1,    0, 0, 0, 1,    1, 1, 0, 1 }, // $3   LDA $13
  { 0, 1, 0, 0,    0, 0, 1, 0,    1, 1, 1, 0 }, // $4   ADD $14
  { 0, 1, 0, 1,    0, 1, 1, 1,    0, 0, 0, 0 }, // $5   JC  $0
  { 0, 1, 1, 0,    1, 1, 1, 0,    1, 1, 1, 0 }, // $6   OUT
  { 0, 1, 1, 1,    0, 1, 0, 1,    1, 1, 1, 1 }, // $7   STA $15
  { 1, 0, 0, 0,    0, 0, 0, 1,    1, 1, 1, 0 }, // $8   LDA $14
  { 1, 0, 0, 1,    0, 1, 0, 1,    1, 1, 0, 1 }, // $9   STA $13
  { 1, 0, 1, 0,    0, 0, 0, 1,    1, 1, 1, 1 }, // $10  LDA $15
  { 1, 0, 1, 1,    0, 1, 0, 1,    1, 1, 1, 0 }, // $11  STA $14
  { 1, 1, 0, 0,    0, 1, 0, 0,    0, 0, 1, 1 }, // $12  JMP $3
  { 1, 1, 0, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // $13
  { 1, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // $14
  { 1, 1, 1, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // $15
};

// Improved code for start of sequence; sequence end at 144.
int FIBONACCI_PROGRAM_3[MEMORY_ADDRESSES /*4 digits*/][MEMORY_ADDRESSES_PINS /*4 digits*/ + MEMORY_PINS /*4 digits*/] = {
  { 0, 0, 0, 0,    0, 1, 1, 0,    0, 0, 0, 1 }, // $0   LDI #1
  { 0, 0, 0, 1,    0, 1, 0, 1,    1, 1, 1, 0 }, // $1   STA $14
  { 0, 0, 1, 0,    0, 1, 1, 0,    0, 0, 0, 0 }, // $2   LDI #0
  { 0, 0, 1, 1,    1, 1, 1, 0,    0, 0, 0, 0 }, // $3   OUT
  { 0, 1, 0, 0,    0, 0, 1, 0,    1, 1, 1, 0 }, // $4   ADD $14
  { 0, 1, 0, 1,    0, 1, 0, 1,    1, 1, 1, 1 }, // $5   STA $15
  { 0, 1, 1, 0,    0, 0, 0, 1,    1, 1, 1, 0 }, // $6   LDA $14
  { 0, 1, 1, 1,    0, 1, 0, 1,    1, 1, 0, 1 }, // $7   STA $13
  { 1, 0, 0, 0,    0, 0, 0, 1,    1, 1, 1, 1 }, // $8   LDA $15
  { 1, 0, 0, 1,    0, 1, 0, 1,    1, 1, 1, 0 }, // $9	  STA $14
  { 1, 0, 1, 0,    0, 0, 0, 1,    1, 1, 0, 1 }, // $10  LDA $13
  { 1, 0, 1, 1,    0, 1, 1, 1,    0, 0, 0, 0 }, // $11  JC  $0
  { 1, 1, 0, 0,    0, 1, 0, 0,    0, 0, 1, 1 }, // $12  JMP $3
  { 1, 1, 0, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // $13
  { 1, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // $14
  { 1, 1, 1, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // $15
};

// Best option as of 13.08.2022. Sequence start at 1; end at 233.
int FIBONACCI_PROGRAM_4[MEMORY_ADDRESSES /*4 digits*/][MEMORY_ADDRESSES_PINS /*4 digits*/ + MEMORY_PINS /*4 digits*/] = {
  { 0, 0, 0, 0,    0, 1, 1, 0,    0, 0, 0, 1 }, // $0   LDI #1
  { 0, 0, 0, 1,    0, 1, 0, 1,    1, 1, 1, 0 }, // $1   STA $14
  { 0, 0, 1, 0,    0, 1, 1, 0,    0, 0, 0, 0 }, // $2   LDI #0
  { 0, 0, 1, 1,    0, 0, 1, 0,    1, 1, 1, 0 }, // $3   ADD $14
  { 0, 1, 0, 0,    0, 1, 0, 1,    1, 1, 1, 1 }, // $4   STA $15
  { 0, 1, 0, 1,    0, 1, 1, 1,    0, 0, 0, 0 }, // $5   JC  $0
  { 0, 1, 1, 0,    1, 1, 1, 0,    0, 0, 0, 0 }, // $6   OUT
  { 0, 1, 1, 1,    0, 0, 0, 1,    1, 1, 1, 0 }, // $7   LDA $14
  { 1, 0, 0, 0,    0, 1, 0, 1,    1, 1, 0, 1 }, // $8   STA $13
  { 1, 0, 0, 1,    0, 0, 0, 1,    1, 1, 1, 1 }, // $9   LDA $15
  { 1, 0, 1, 0,    0, 1, 0, 1,    1, 1, 1, 0 }, // $10  STA $14
  { 1, 0, 1, 1,    0, 0, 0, 1,    1, 1, 0, 1 }, // $11  LDA $13
  { 1, 1, 0, 0,    0, 1, 0, 0,    0, 0, 1, 1 }, // $12  JMP $3
  { 1, 1, 0, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // $13
  { 1, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // $14
  { 1, 1, 1, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // $15
  //  { 1, 1, 1, 1,    1, 0, 1, 0,    1, 0, 1, 0 }, // $15 PATTERN for test only

};

// Work in progress as of 13.08.2022. Sequence start at 1; end at 233; after 233 --> 121 (121 + 256 = 377 (= 233 + 144))
int FIBONACCI_PROGRAM_5[MEMORY_ADDRESSES /*4 digits*/][MEMORY_ADDRESSES_PINS /*4 digits*/ + MEMORY_PINS /*4 digits*/] = {
  { 0, 0, 0, 0,    0, 1, 1, 0,    0, 0, 0, 1 }, // $0   LDI #1
  { 0, 0, 0, 1,    0, 1, 0, 1,    1, 1, 1, 0 }, // $1   STA $14
  { 0, 0, 1, 0,    0, 1, 1, 0,    0, 0, 0, 0 }, // $2   LDI #0
  { 0, 0, 1, 1,    0, 0, 1, 0,    1, 1, 1, 0 }, // $3   ADD $14
  { 0, 1, 0, 0,    1, 1, 1, 0,    0, 0, 0, 0 }, // $4   OUT
  { 0, 1, 0, 1,    0, 1, 0, 1,    1, 1, 1, 1 }, // $5   STA $15
  { 0, 1, 1, 0,    0, 1, 1, 1,    0, 0, 0, 0 }, // $6   JC  $0
  { 0, 1, 1, 1,    0, 0, 0, 1,    1, 1, 1, 0 }, // $7   LDA $14
  { 1, 0, 0, 0,    0, 1, 0, 1,    1, 1, 0, 1 }, // $8   STA $13
  { 1, 0, 0, 1,    0, 0, 0, 1,    1, 1, 1, 1 }, // $9   LDA $15
  { 1, 0, 1, 0,    0, 1, 0, 1,    1, 1, 1, 0 }, // $10  STA $14
  { 1, 0, 1, 1,    0, 0, 0, 1,    1, 1, 0, 1 }, // $11  LDA $13
  { 1, 1, 0, 0,    0, 1, 0, 0,    0, 0, 1, 1 }, // $12  JMP $3
  { 1, 1, 0, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // $13
  { 1, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // $14
  { 1, 1, 1, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // $15
};

int COUNTER_PROGRAM[MEMORY_ADDRESSES][MEMORY_ADDRESSES_PINS + MEMORY_PINS] = {
  { 0, 0, 0, 0,    0, 0, 1, 0,    1, 1, 1, 1 }, // $0   ADD $15
  { 0, 0, 0, 1,    1, 1, 1, 0,    0, 0, 0, 0 }, // $1   OUT
  { 0, 0, 1, 0,    0, 1, 1, 1,    0, 1, 0, 0 }, // $2   JC  $4
  { 0, 0, 1, 1,    0, 1, 0, 0,    0, 0, 0, 0 }, // $3   JMP $0
  { 0, 1, 0, 0,    0, 0, 1, 1,    1, 1, 1, 1 }, // $4   SUB $15
  { 0, 1, 0, 1,    1, 1, 1, 0,    0, 0, 0, 0 }, // $5   OUT
  { 0, 1, 1, 0,    1, 0, 0, 0,    0, 0, 0, 0 }, // $6   JZ  $0
  { 0, 1, 1, 1,    0, 1, 0, 0,    0, 1, 0, 0 }, // $7   JMP $4
  { 1, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // $8
  { 1, 0, 0, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // $9
  { 1, 0, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // $10
  { 1, 0, 1, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // $11
  { 1, 1, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // $12
  { 1, 1, 0, 1,    0, 0, 0, 0,    0, 0, 0, 0 }, // $13
  { 1, 1, 1, 0,    0, 0, 0, 0,    0, 0, 0, 0 }, // $14
  { 1, 1, 1, 1,    0, 0, 0, 0,    0, 0, 0, 1 }, // $15
};


/*
   Set Arduino pins for computer Program Mode
*/
void set_for_programming() {
  digitalWrite(MEMORY_PROGRAMMING_MODE, HIGH);    // pin Program (HI) / Run (LO) mode
  digitalWrite(START_STOP_CLOCK, HIGH);           // pin Clock on/off (clock active LO)
  digitalWrite(WRITE_TO_MEMORY, HIGH);            // pin Write to Memory (active LO) (push button)
  digitalWrite(RESET_COMPUTER, HIGH);             // pin Reset (active LO)

  pinMode(MEMORY_PROGRAMMING_MODE, OUTPUT);
  pinMode(START_STOP_CLOCK, OUTPUT);
  pinMode(WRITE_TO_MEMORY, OUTPUT);
  pinMode(RESET_COMPUTER, OUTPUT);

  pinMode(MEMORY_PIN_0, OUTPUT);
  pinMode(MEMORY_PIN_1, OUTPUT);
  pinMode(MEMORY_PIN_2, OUTPUT);
  pinMode(MEMORY_PIN_3, OUTPUT);
  pinMode(MEMORY_PIN_4, OUTPUT);
  pinMode(MEMORY_PIN_5, OUTPUT);
  pinMode(MEMORY_PIN_6, OUTPUT);
  pinMode(MEMORY_PIN_7, OUTPUT);
  pinMode(MEMORY_ADDRESS_PIN_0, OUTPUT);
  pinMode(MEMORY_ADDRESS_PIN_1, OUTPUT);
  pinMode(MEMORY_ADDRESS_PIN_2, OUTPUT);
  pinMode(MEMORY_ADDRESS_PIN_3, OUTPUT);
  digitalWrite(MEMORY_PROGRAMMING_MODE, LOW); 
}

/*
   Set Arduino pins for computer Run Mode
*/
void post_programming() {
  digitalWrite(MEMORY_PROGRAMMING_MODE, HIGH);
  //~ delay(10);
  digitalWrite(START_STOP_CLOCK, LOW);
  digitalWrite(RESET_COMPUTER, HIGH);
  digitalWrite(RESET_COMPUTER, LOW);
  delay(10);
  // porto a Input tutti i PIN così passano in HI-Z
  pinMode(MEMORY_PROGRAMMING_MODE, INPUT);
  pinMode(START_STOP_CLOCK, INPUT);
  pinMode(WRITE_TO_MEMORY, INPUT);
  pinMode(RESET_COMPUTER, INPUT);
  pinMode(MEMORY_PIN_0, INPUT);
  pinMode(MEMORY_PIN_1, INPUT);
  pinMode(MEMORY_PIN_2, INPUT);
  pinMode(MEMORY_PIN_3, INPUT);
  pinMode(MEMORY_PIN_4, INPUT);
  pinMode(MEMORY_PIN_5, INPUT);
  pinMode(MEMORY_PIN_6, INPUT);
  pinMode(MEMORY_PIN_7, INPUT);
  pinMode(MEMORY_ADDRESS_PIN_0, INPUT);
  pinMode(MEMORY_ADDRESS_PIN_1, INPUT);
  pinMode(MEMORY_ADDRESS_PIN_2, INPUT);
  pinMode(MEMORY_ADDRESS_PIN_3, INPUT);
}

/*
   Write a program to memory.
*/
void writeProgram(int program[MEMORY_ADDRESSES][MEMORY_ADDRESSES_PINS + MEMORY_PINS]) {
  for (int command = 0; command < MEMORY_ADDRESSES; command += 1) {
    digitalWrite(MEMORY_ADDRESS_PIN_3, program[command][0]);
    digitalWrite(MEMORY_ADDRESS_PIN_2, program[command][1]);
    digitalWrite(MEMORY_ADDRESS_PIN_1, program[command][2]);
    digitalWrite(MEMORY_ADDRESS_PIN_0, program[command][3]);
    digitalWrite(MEMORY_PIN_7, program[command][4]);
    digitalWrite(MEMORY_PIN_6, program[command][5]);
    digitalWrite(MEMORY_PIN_5, program[command][6]);
    digitalWrite(MEMORY_PIN_4, program[command][7]);
    digitalWrite(MEMORY_PIN_3, program[command][8]);
    digitalWrite(MEMORY_PIN_2, program[command][9]);
    digitalWrite(MEMORY_PIN_1, program[command][10]);
    digitalWrite(MEMORY_PIN_0, program[command][11]);
    digitalWrite(WRITE_TO_MEMORY, LOW);
    delayMicroseconds(10);
    digitalWrite(WRITE_TO_MEMORY, HIGH);
    delay(150);
  }
}


////////////////////////////////////////////////////////////
////////////// KITT supercar LEDs effect ///////////////////
////////////////////////////////////////////////////////////

int KITT[LEDS][PINS] = {
  { 0, 0, 0, 0, 0, 0, 0, 1 },
  { 0, 0, 0, 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 0, 0 },
  { 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0 },
  //~ { 0, 0, 0, 0, 0, 0, 0, 1 },
  //~ { 0, 0, 0, 0, 0, 0, 0, 0 },
};

/*
   LEDs moving as KITT supercar; shown at end of programming
*/
void writeKitt(int led_array[LEDS][PINS]) {
  //~ Save content of memory address $15 because it is used for LED effect
  digitalWrite(MEMORY_ADDRESS_PIN_3, 1);
  digitalWrite(MEMORY_ADDRESS_PIN_2, 1);
  digitalWrite(MEMORY_ADDRESS_PIN_1, 1);
  digitalWrite(MEMORY_ADDRESS_PIN_0, 1);
  for (int pin = MEMORY_PIN_7; pin >= MEMORY_PIN_0; pin -= 1) {
    pinMode(pin, INPUT);
    led_array[16][pin] = digitalRead(pin);
    pinMode(pin, OUTPUT);
//    Serial.println("\n+++++++++++++++++++++++++++++");
//    Serial.print("Numero pin: ");
//    Serial.print(pin);
//    Serial.print("; ");
//    Serial.print("Valore: ");
//    Serial.println(led_array[16][pin]);
  }

  //~ Actual LEDs effect
  for (int times = 1; times <= 3; times += 1) {
    for (int led_sequence = 0; led_sequence < LEDS; led_sequence += 1) {
      digitalWrite(MEMORY_ADDRESS_PIN_3, 1);
      digitalWrite(MEMORY_ADDRESS_PIN_2, 1);
      digitalWrite(MEMORY_ADDRESS_PIN_1, 1);
      digitalWrite(MEMORY_ADDRESS_PIN_0, 1);
      digitalWrite(MEMORY_PIN_7, led_array[led_sequence][0]);
      digitalWrite(MEMORY_PIN_6, led_array[led_sequence][1]);
      digitalWrite(MEMORY_PIN_5, led_array[led_sequence][2]);
      digitalWrite(MEMORY_PIN_4, led_array[led_sequence][3]);
      digitalWrite(MEMORY_PIN_3, led_array[led_sequence][4]);
      digitalWrite(MEMORY_PIN_2, led_array[led_sequence][5]);
      digitalWrite(MEMORY_PIN_1, led_array[led_sequence][6]);
      digitalWrite(MEMORY_PIN_0, led_array[led_sequence][7]);
      digitalWrite(WRITE_TO_MEMORY, LOW);
      delayMicroseconds(10);
      digitalWrite(WRITE_TO_MEMORY, HIGH);
      delay(60);
    }
  }
  //~ Restore content of memory address $15
  digitalWrite(MEMORY_ADDRESS_PIN_3, 1);
  digitalWrite(MEMORY_ADDRESS_PIN_2, 1);
  digitalWrite(MEMORY_ADDRESS_PIN_1, 1);
  digitalWrite(MEMORY_ADDRESS_PIN_0, 1);
  for (int pin = MEMORY_PIN_7; pin >= MEMORY_PIN_0; pin -= 1) {
    digitalWrite(pin, led_array[16][pin]);
    digitalWrite(WRITE_TO_MEMORY, LOW);
    delayMicroseconds(10);
    digitalWrite(WRITE_TO_MEMORY, HIGH);
    delay(10);
  }
  //~ delay(500);
}


/*
   Setup the Arduino program.

   Both write to memory and memory programming mode pins need to write
   low to SN74LS157N's first pin to select DIP switches what is neeeded
   for Arduino to put a program into the memory. When it's high, then
   the computer is working in the run mode.

   References:
     - https://youtu.be/KNve2LCcSRc?t=900
*/
void setup() {
  Serial.begin(115200);
  delay(300);
}

void loop() {
  set_for_programming();
  writeProgram(FIBONACCI_PROGRAM_4);
  writeKitt(KITT);
  post_programming();
  delay(120000);
  set_for_programming();
  writeProgram(COUNTER_PROGRAM);
  writeKitt(KITT);
  post_programming();
  delay(240000);
}
