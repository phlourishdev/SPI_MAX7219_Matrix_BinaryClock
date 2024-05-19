void init_MAX7219(void) {
  // configuration
  send_to_MAX7219(0x09, 0x00);  // Decoding off (0xAddr Data)
  send_to_MAX7219(0x0A, 0x08);  // Brightness to intermediate
  send_to_MAX7219(0x0B, 0x07);  // Scan limit = 7
  send_to_MAX7219(0x0C, 0x01);  // Normal operation mode
  send_to_MAX7219(0x0F, 0x0F);  // Enable display test
  send_to_MAX7219(0x0F, 0x00);  // Disable display test
  delay(500);                   // safety delay

  // clear every row
  for (int i = 1; i <= 8; i++) {
    send_to_MAX7219(i, 0x00);
  }

  Serial.println("Initialized MAX7219");
  delay(500); // safety delay
}

// row (of the matrix) includes the MSB,
// column (of the matrix) includes the LSB
void send_to_MAX7219(unsigned char row, unsigned char column) {
  // write to SPI bus
  digitalWrite(CS, LOW);
  SPI.transfer(row);
  SPI.transfer(column);
  digitalWrite(CS, HIGH);
}
