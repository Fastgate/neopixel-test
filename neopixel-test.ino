#include <FastLED.h>
#include "ledcontrol.h"
#include "ledeffects.h"

#define NUM_LEDS 120
#define DATA_PIN 2
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define BRIGHTNESS 128

CRGB leds[NUM_LEDS];

PixelGroup<0, 20> group1(leds, &FastLED);
PixelGroup<20, 20> group2(leds, &FastLED);
PixelGroup<40, 20> group3(leds, &FastLED);
PixelGroup<60, 20> group4(leds, &FastLED);
PixelGroup<80, 20> group5(leds, &FastLED);
PixelGroup<100, 20> group6(leds, &FastLED);

SweepEffect sweep1(CRGB::CornflowerBlue, 10);
SweepEffect sweep2(CRGB::Crimson, 10);
SweepEffect sweep3(CRGB::Maroon, 100);
ConfettiEffect confetti(0.2);
RainbowEffect rainbow(CHSV(0, 240, 255), 5, 20);
PulseEffect pulse(CRGB::Pink, 1);

void setup() {
	pinMode(DATA_PIN, OUTPUT);

	delay(500);

	FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	FastLED.setBrightness(BRIGHTNESS);

	group1.set(CRGB::CornflowerBlue);
	group2.set(CRGB::Crimson);
	group3.set(CRGB::DeepSkyBlue);
	group4.set(CRGB::DeepPink);
	group5.set(CRGB::FairyLightNCC);

	sweep1.setLength(10);
	sweep1.addGroup(&group1);

	sweep2.setLength(10);
	sweep2.setDirection(-1);
	sweep2.addGroup(&group2);

	sweep3.setLength(5);
	sweep3.setBidirectional(true);
	sweep3.addGroup(&group3);

	confetti.addGroup(&group4);

	rainbow.addGroup(&group5);

	pulse.addGroup(&group6);
}

void loop() {
	sweep1.update(&FastLED);
	sweep2.update(&FastLED);
	sweep3.update(&FastLED);
	confetti.update(&FastLED);
	rainbow.update(&FastLED);
	pulse.update(&FastLED);
}
