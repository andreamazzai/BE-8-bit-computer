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

/*
 * Fibonacci program.
 * References: - https://youtu.be/a73ZXDJtU48?t=263
 * Restarts from scratch when Carry is set (calculation > 255)
 */
int FIBONACCI_PROGRAM[MEMORY_ADDRESSES /*4 digits*/][MEMORY_ADDRESSES_PINS /*4 digits*/+ MEMORY_PINS /*4 digits*/] = {
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
   Write a program to the memory.
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
    delayMicroseconds(1);
    digitalWrite(WRITE_TO_MEMORY, HIGH);
    delay(250);
  }
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
  pinMode(MEMORY_PROGRAMMING_MODE, OUTPUT);
  pinMode(WRITE_TO_MEMORY, OUTPUT);
  pinMode(RESET_COMPUTER, OUTPUT);

  /*
     porto a HI i TRI e THR del 555 bistabile di uscita così passo in modalità clock manuale
     poi riporto il pin a INPUT così va in HI-Z
  */
  digitalWrite(START_STOP_CLOCK, HIGH);
  pinMode(START_STOP_CLOCK, OUTPUT);
  delay(200);
  pinMode(START_STOP_CLOCK, INPUT);

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

  digitalWrite(WRITE_TO_MEMORY, HIGH);
  digitalWrite(MEMORY_PROGRAMMING_MODE, LOW);

  writeProgram(FIBONACCI_PROGRAM);
  // writeProgram(COUNTER_PROGRAM);

  digitalWrite(MEMORY_PROGRAMMING_MODE, HIGH);
  delay(1000);

  /*
     porto a LO i TRI e THR del 555 bistabile di uscita così passo in modalità clock automatico
     poi riporto il pin a INPUT così va in HI-Z
  */

  digitalWrite(START_STOP_CLOCK, LOW);
  pinMode(START_STOP_CLOCK, OUTPUT);
  delay(200);
  pinMode(START_STOP_CLOCK, INPUT);

  digitalWrite(RESET_COMPUTER, HIGH);
  digitalWrite(RESET_COMPUTER, LOW);
}

void loop() {}
