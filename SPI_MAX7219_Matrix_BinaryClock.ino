#include <SPI.h>
#include <EEPROM.h>

#define CS D10
#define ELEMENT_AMOUNT 6  // 6 for { H, H, M, M, S, S}

// set hardware timer
static HardwareTimer timer2 = HardwareTimer(TIM2);

// set EEPROM addresses
const int SecEepromAddress = 0, MinEepromAddress = 1, HrEepromAddress = 2;

// declare non-const vars
int secs, mins, hrs;
int time_segments[ELEMENT_AMOUNT];

void ISR_Timer2(void) {
  secs++;
  update_clock();
}

void setup() {
  // initialize serial monitor
  Serial.begin(115200);

  // configure chip select
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);

  // configure SPI bus
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  SPI.setDataMode(SPI_MODE0);

  // call MAX7219 initialization func
  init_MAX7219();

  // call EEPROM initialization func
  init_EEPROM();

  // configure timer
  timer2.setOverflow(1, HERTZ_FORMAT);
  timer2.attachInterrupt(ISR_Timer2);
  timer2.resume();

  Serial.println("Setup done");
}

void loop() {
  if (Serial.available() > 0) {
    set_time();
  }

  // display hours
  send_to_MAX7219(0x01, time_segments[0]);
  send_to_MAX7219(0x02, time_segments[1]);

  // display minutes
  send_to_MAX7219(0x04, time_segments[2]);
  send_to_MAX7219(0x05, time_segments[3]);

  // display seconds
  send_to_MAX7219(0x07, time_segments[4]);
  send_to_MAX7219(0x08, time_segments[5]);
}
