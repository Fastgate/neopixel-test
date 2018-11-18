#include <FastLED.h>
#include "ledcontrol.h"

#define NUM_LEDS 52
#define DATA_PIN 0
#define COLOR_ORDER RGB
#define CHIPSET WS2812B
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];

PixelGroup<0, 1> dimmerButtonMinus(leds, &FastLED);
PixelGroup<52, 1> dimmerButtonPlus(leds, &FastLED);

PixelGroup<9, 21> rpmMeterScale(leds, &FastLED);
PixelGroup<32, 1> rpmMeterNeedle(leds, &FastLED);
PixelGroup<33, 1> shiftLight(leds, &FastLED);

PixelGroup<34, 12> speedoScale(leds, &FastLED);
PixelGroup<50, 1> speedoNeedle(leds, &FastLED);
PixelGroup<30, 1> gearNumberDisplay(leds, &FastLED);
PixelGroup<31, 1> synchroRevDisplay(leds, &FastLED);

PixelGroup<46, 4> odometer(leds, &FastLED);
PixelGroup<1, 9> boardComputer(leds, &FastLED);


void setup() {
  delay(3000);

  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  dimmerButtonMinus.set(CRGB::Blue);
  dimmerButtonPlus.set(CRGB::Blue);

  rpmMeterScale.set(CRGB::White);
  rpmMeterNeedle.set(CRGB::Red);

  speedoScale.set(CRGB::White);
  speedoNeedle.set(CRGB::Red);
  gearNumberDisplay.set(CRGB::Pink);
  synchroRevDisplay.set(CRGB::Green);
  
  odometer.set(CRGB::Orange);
  boardComputer.set(CRGB::Orange);
}

void loop() {   
   shiftLight.set(CRGB::Red);
   delay(500);
   shiftLight.set(CRGB::Black);
   delay(500);
}
