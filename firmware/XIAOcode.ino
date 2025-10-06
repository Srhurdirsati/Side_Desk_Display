#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold12pt7b.h>

// --- Pin Mapping ---
#define EPD_BUSY 4
#define EPD_RST  5
#define EPD_DC   6
#define EPD_CS   7
#define EPD_CLK  8
#define EPD_DIN 10

// E-paper instance
GxEPD2_BW<GxEPD2_420, GxEPD2_420::HEIGHT> display(GxEPD2_420(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

String incoming = "";
bool newData = false;

void setup() {
  Serial.begin(115200);
  display.init(115200);
  display.setRotation(1);

  clearScreen();
}

void loop() {
  // Read from Serial
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {   // end of message
      newData = true;
    } else {
      incoming += c;
    }
  }

  // If new data arrived
  if (newData) {
    drawScreen(incoming);
    incoming = "";
    newData = false;
  }
}

void clearScreen() {
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
  } while (display.nextPage());
}

void drawScreen(String msg) {
  clearScreen();
  display.setFont(&FreeMonoBold12pt7b);
  display.setTextColor(GxEPD_BLACK);

  display.setFullWindow();
  display.firstPage();
  do {
    int16_t x = 20, y = 50;
    display.setCursor(x, y);
    display.print(msg);   // print full string from PC
  } while (display.nextPage());
}
