void set_time(void) {
  // read and trim string from serial
  String read = Serial.readString();
  read.trim();

  // if read as long as "set HH:MM:SS"
  if (read.length() == 12 && read.substring(0, 3) == "set") {
    // get HH:MM:SS only
    String timePart = read.substring(4, 12);

    // get indexes of ":" character
    int firstColon = timePart.indexOf(":");
    int secondColon = timePart.lastIndexOf(":");

    // if format with ":" is correct
    if (firstColon == 2 && secondColon == 5) {
      // seperate time values and convert them to int
      int newHr = timePart.substring(0, 2).toInt();
      int newMin = timePart.substring(3, 5).toInt();
      int newSec = timePart.substring(6, 8).toInt();

      // check if time values are in valid range
      if (newHr >= 0 && newHr <= 23 && newMin >= 0 && newMin <= 59 && newSec >= 0 && newSec <= 59) {
        // set new values as time values
        hrs = newHr;
        mins = newMin;
        secs = newSec;
        Serial.println("New time set:  " + timePart);
      } else {
        Serial.println("Time values out of valid range");
      }
    }
  } else {
    Serial.println("Usage: set HH:MM:SS");
  }
}