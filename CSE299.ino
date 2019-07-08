#include <NewPing.h>            // ultrasound sensor library
#include <Adafruit_GFX.h>       // for writing text/graphics to screen
#include <Adafruit_SSD1306.h>   // driver library for oleds with 1306 driver chip
 
#define OLED_Address 0x3C       // I2C address of oled, if this doesn't work try 0x3D
Adafruit_SSD1306 oled(128,64);  // create our screen object setting resolution to 128x64
 
#define NUM_OF_READINGS 10      // number of readings to take before using highest for display
                                // This gives a less jittery stable value
                                // But at the expense of taking longer to update display
                                // A value of 10 will be 0.5s per update to display
 
#define TRIGGER_PIN  12         // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11         // Arduino pin tied to echo pin on the ultrasonic sensor.
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN); // NewPing setup of pins
void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);     // init the display
} 
    
long Distance;                  // Highest reading in the last samples to display
long ThisReading;               // and last red current reading
 
void loop() {
  // Take readings, go with highest, from experimentation the highest from a range
  // of samples is usaully the correct one with lower values being spurious
  Distance=0;
  for(int i=0;i<NUM_OF_READINGS;i++)
  {
    delay(50);                     // Wait 50ms between pings (20 pings/sec). 29ms should be the shortest delay between pings.
    ThisReading=sonar.ping_cm();
    if(ThisReading>Distance)
      Distance=ThisReading;
  }
  // Display result to display
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setTextSize(2);
  oled.setCursor(0,0);
  oled.print("Distance :");
  oled.print(Distance);
  oled.println("cm");
  oled.display();
}
