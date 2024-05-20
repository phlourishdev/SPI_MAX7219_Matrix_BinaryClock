## SPI_MAX7219_Matrix_BinaryClock 
Implements a binary clock for a MAX7219 8x8 matrix display. Tested on STM32 Nucleo64 L152RE.

### How a binary clock works
As the image below demonstrates, every column represents a decimal digit.

<a title="Alexander Jones &amp; Eric Pierce, CC BY-SA 3.0 &lt;http://creativecommons.org/licenses/by-sa/3.0/&gt;, via Wikimedia Commons" href="https://commons.wikimedia.org/wiki/File:Binary_clock.png"><img width="350" alt="Binary clock" src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/72/Binary_clock.png/512px-Binary_clock.png?20060605215758"></a>

### Setting the time
To set the time, use the following command through the serial monitor. Make sure the serial monitor is set to 115200 baud.
```shell
set HH:MM:SS
```
For example, for 10 hours, 37 minutes, and 49 seconds, you would use the following.
```shell
set 10:37:49
```
