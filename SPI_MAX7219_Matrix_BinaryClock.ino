#include <SPI.h>

#define CS D10
#define ELEMENT_AMOUNT 6  // 6 for { H, H, M, M, S, S}

static HardwareTimer timer2 = HardwareTimer(TIM2);

int secs, mins, hrs;
int time_segments[ELEMENT_AMOUNT];

void ISR_Timer2(void) {
  secs++;
  update_clock();
}

void setup() {
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

  // configure timer
  timer2.setOverflow(1, HERTZ_FORMAT);
  timer2.attachInterrupt(ISR_Timer2);
  timer2.resume();

  // initialize serial monitor
  Serial.begin(115200);

  Serial.println("Setup done");
}

void loop() {
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
