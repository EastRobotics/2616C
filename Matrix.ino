
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8,1,2, PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT+
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(24);
  matrix.setTextColor(colors[0]);
  matrix.setTextSize(2);

}

int x    = matrix.width();
int pass = 0;


void loop() {
  matrix.fillScreen(0);
  matrix.setCursor(x, 2);
  matrix.print("J&J Snack Foods Corp.");
  if(--x < -350) {
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(100);

}
