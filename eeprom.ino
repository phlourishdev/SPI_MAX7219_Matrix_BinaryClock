void init_EEPROM(void) {
  EEPROM.begin();
  // if value for seconds, that is read from EEPROM, is invalid
  if (EEPROM.read(SecEepromAddress) < 0 || EEPROM.read(SecEepromAddress) >= 60) {
    Serial.println("Read EEPROM values invalid, setting new values");

    // set default time values
    secs = 0;
    mins = 0;
    hrs = 0;

    // write them to EEPROM
    write_time_to_EEPROM();
  } else {
    // else read time values from EEPROM
    Serial.println("EEPROM values valid, copying them");
    secs = EEPROM.read(SecEepromAddress);
    mins = EEPROM.read(MinEepromAddress);
    hrs = EEPROM.read(HrEepromAddress);
  }
}

void write_time_to_EEPROM(void) {
  EEPROM.write(SecEepromAddress, secs);
  EEPROM.write(MinEepromAddress, mins);
  EEPROM.write(HrEepromAddress, hrs);
}