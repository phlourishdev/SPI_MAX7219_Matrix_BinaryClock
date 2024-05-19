void update_clock(void) {
  // clock logic
  if (secs >= 60) {
    secs = 0;
    mins++;
  }
  if (mins >= 60) {
    mins = 0;
    hrs++;
  }
  if (hrs >= 24) {
    hrs = 0;
  }

  // output current time
  char clock_buf[16];
  sprintf(clock_buf, "%02u:%02u:%02u", hrs, mins, secs);
  Serial.println("Updated Clock: " + String(clock_buf));

  // call segment update func
  update_time_segments();
}

void update_time_segments(void) {
  int times[3] = { secs, mins, hrs };

  // split time values into tens and ones and put into array
  for (int i = 0; i < 3; i++) {
    time_segments[2 * i] = times[i] % 10;
    time_segments[2 * i + 1] = times[i] / 10;
  }

  // move elements bitwise so that time is displayed centered
  for (int i = 0; i < ELEMENT_AMOUNT; i++) {
    time_segments[i] = time_segments[i] << 2;
  }
}