#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)



 //MISC icon
#define LOGO_HEIGHT 36
#define LOGO_WIDTH 25

const uint8_t PROGMEM misc_icon[] = {
0x00, 0x03, 0xe0, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x0f, 0x80, 0x00,
0x00, 0x1f, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x00,
0x01, 0xff, 0xfe, 0x00, 0x03, 0xff, 0xfe, 0x00, 0x03, 0xff, 0xfe, 0x00, 0x07, 0xc0, 0x3f, 0x00,
0x0f, 0x80, 0x1f, 0x00, 0x1f, 0x20, 0x5f, 0x00, 0x3e, 0x60, 0xcf, 0x80, 0x7c, 0xe1, 0xcf, 0x80,
0x7d, 0xf3, 0xef, 0x80, 0xf9, 0xf3, 0xef, 0x80, 0xf8, 0x00, 0x0f, 0x80, 0xf8, 0x18, 0x1f, 0x00,
0xf8, 0x18, 0x3f, 0x00, 0xfc, 0x38, 0x3e, 0x00, 0x7c, 0x7c, 0x7c, 0x00, 0x7c, 0xfc, 0xf8, 0x00,
0x7e, 0x01, 0xf0, 0x00, 0x3f, 0xff, 0xe0, 0x00, 0x3f, 0xff, 0xe0, 0x00, 0x3f, 0xff, 0xc0, 0x00,
0x1f, 0xff, 0x80, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00,
0x00, 0xf8, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00
};

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.display();
  delay(3000);
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    misc_icon, LOGO_WIDTH, LOGO_HEIGHT, 1);
    display.display();

  delay (3000);
  display.clearDisplay();

  testanimate(misc_icon, LOGO_WIDTH, LOGO_HEIGHT); // Animate misc_icon bitmap
}

void loop() {}

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2
#define NUMLOGOS 3

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMLOGOS][3];

  // Initialize 'snowflake' positions
  for(f=0; f< NUMLOGOS; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    Serial.print(F("x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { // Loop forever...
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMLOGOS; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(200);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMLOGOS; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}

    
 
