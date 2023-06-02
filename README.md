# IoTRoboLink
Welcome to the IoTRoboLink repository!

## About
IoTRoboLink is a collection of my personal projects in the field of IoT and robotics. The projects showcased here utilize Arduino and NodeMCU platforms to develop innovative and interactive systems.

## Project
### 001_IOT-Clock-With-NTP.ino
- The code you provided is an Arduino sketch that utilizes various libraries to control an ESP8266 microcontroller and display the current time and date on an LCD using the I2C interface.
- The code begins by including the necessary libraries, including the ESP8266WiFi, WiFiUdp, NTPClient, TimeLib, and LiquidCrystal_I2C libraries. The LiquidCrystal_I2C object lcd is then created, specifying the I2C address of the LCD module (0x27) and the number of columns and rows.
- You need to replace "YOUR_WIFI" with the name of your Wi-Fi network and "YOUR_WIFI_PASSWORD" with the corresponding password. The ssid variable holds the Wi-Fi network name, and the pw variable holds the Wi-Fi password. The utcOffsetInSeconds variable represents the UTC offset in seconds for your time zone. The ntpUDP object is created for NTP (Network Time Protocol) communication, and the timeClient object is created with the NTP server address and the UTC offset.
- The code declares several variables used to store and manipulate the time and date values. Time is a character array to hold the formatted time string, and Date is a character array to hold the formatted date string. Other variables such as last_second, second_, minute_, hour_, day_, month_, year_, i, and led are declared for further use.
- In this section, the led pin is set as an output pin using pinMode() function. This pin is used to control an external LED. Then, the LCD is initialized using the init() function, and the backlight is turned on using the backlight() function. The LCD is cleared, and the text "Aan Aryoo" is printed on the first row of the LCD at position (3, 0) using setCursor() and print() functions. Similarly, the text "NEA" is printed on the second row of the LCD at position (6, 1).
- In this part, the ESP8266 attempts to connect to the Wi-Fi network specified by the ssid and pw variables using the WiFi.begin() function. While the connection is not established (WiFi.status() != WL_CONNECTED), it enters a loop where it displays "Connecting" on the LCD. The loop cycles through displaying periods (".") to indicate progress. After a successful connection, the LCD is cleared, and "Connected!" is displayed on the first row of the LCD, while "NICE" is displayed on the second row.
- A delay of 2000 milliseconds (2 seconds) is added before calling timeClient.begin() to ensure a stable connection. The timeClient object is initialized to start retrieving the time from the NTP server specified earlier.
- The loop() function is where the main execution of the program occurs in a continuous loop.
- The first part of the loop retrieves the updated time from the NTP server by calling timeClient.update(). It then gets the current time in the form of a Unix epoch timestamp using timeClient.getEpochTime() and stores it in the unix_epoch variable.
- Next, the current time is extracted from the Unix epoch timestamp. The seconds, minutes, hours, day, month, and year values are obtained using the second(), minute(), hour(), day(), month(), and year() functions from the TimeLib library.
- The extracted time values are used to update the Time and Date character arrays. The values are converted to ASCII characters and stored in the respective positions of the arrays. This allows the time and date to be displayed correctly on the LCD.
- The LCD display is then updated with the new time and date by calling lcd.print() and passing the Time and Date arrays to it. The LCD cursor is set to the beginning of the first and second rows using lcd.setCursor().
- The last_second variable is updated with the current second value to keep track of when the time changes. This helps prevent unnecessary updates to the LCD display when the time hasn't changed.
- After updating the LCD, the LED connected to the led pin is turned on by setting it to HIGH using digitalWrite(). A delay of 1000 milliseconds (1 second) is added using delay() to keep the LED on for a second. Then, the LED is turned off by setting the led pin to LOW using digitalWrite().
- The loop continues to repeat, updating the time, updating the LCD, and toggling the LED every second.

### 002_PrintOled.ino
- The code sets up and controls a 128x64 OLED display (specifically, an Adafruit SSD1306 display) using the Wire library.
- In the setup() function, the display is initialized by calling display.begin(SSD1306_SWITCHCAPVCC, 0x3C). This sets up the communication with the display using the I2C protocol. The display is cleared using display.clearDisplay(). The text size is set to 1 with display.setTextSize(1), and the text color is set to white using display.setTextColor(SSD1306_WHITE). Additionally, the built-in LED pin is configured as an output using pinMode(LED_BUILTIN, OUTPUT).
- The loop() function is where the main execution of the program occurs in a continuous loop.
- In each iteration of the loop, the display is cleared using display.clearDisplay(). The built-in LED is turned on by setting the LED pin to HIGH using digitalWrite(LED_BUILTIN, HIGH), and there is a delay of 500 milliseconds.
- The next lines of code set the cursor position on the display using display.setCursor(0, i), where i represents the vertical position of the text. The text "Aan Aryo Ganteng" is then printed on the display using display.println("Aan Aryo Ganteng").
- After printing the text, the display is updated to show the changes by calling display.display().
- The built-in LED is turned off by setting the LED pin to LOW using digitalWrite(LED_BUILTIN, LOW).
- The code then checks if i is greater than 48. If so, it resets i to 0; otherwise, it increments i by 8. This controls the vertical position of the text on the display, allowing it to scroll vertically.
- Finally, there is a delay of 500 milliseconds before the next iteration of the loop begins.
- This loop continues, clearing the display, toggling the LED, printing the text, and scrolling the text vertically on the display.
