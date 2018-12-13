#ifndef LEDEFFECTS_H_
#define LEDEFFECTS_H_

#include "ledcontrol.h"

class PulseEffect: public PixelEffect {
private:
	unsigned long totalDeltaTime = 0;
	float speed = 0.5;
	float brightness = 0;
	CRGB color;

	bool isFadingIn = true;

public:
	PulseEffect(CRGB color, float speed) :
			PixelEffect(60) {
		this->speed = speed;
		this->color = color;
	}

	bool beforeFrame(int pixelCount, unsigned long deltaTime) {
		(void) (pixelCount);
		(void) (deltaTime);

		if (this->totalDeltaTime >= 1000 / this->speed) {
			brightness += 1 / (float) 1000 * this->speed;
			return true;
		}
		return true;
	}
	void afterFrame(int pixelCount, unsigned long deltaTime) {
		(void) (pixelCount);

		this->totalDeltaTime += deltaTime;
	}
	void onFrame(struct CRGB * pixel, int pixelIndex, int pixelCount,
			unsigned long deltaTime) {
		(void) (pixelIndex);
		(void) (pixelCount);
		(void) (deltaTime);

		// FIXME this is completely broken
		pixel->r = min(255, this->color.r * brightness);
		pixel->g = min(255, this->color.g * brightness);
		pixel->b = min(255, this->color.b * brightness);
	}
};

class RainbowEffect: public PixelEffect {
private:
	unsigned long totalDeltaTime = 0;
	float speed = 0.5;
	uint8_t delta = 1;
	CHSV hsv;

	uint8_t currentHue = 0;
public:
	RainbowEffect(CHSV hsv, float speed, uint8_t delta) :
			PixelEffect(60) {
		this->speed = speed;
		this->delta = delta;
		this->hsv = hsv;
		this->currentHue = hsv.h;
	}

	bool beforeFrame(int pixelCount, unsigned long deltaTime) {
		(void) (pixelCount);
		(void) (deltaTime);

		if (this->totalDeltaTime >= 1000 / this->speed) {
			this->hsv.hue += 1;
			this->currentHue = this->hsv.hue;
			return true;
		}
		return true;
	}
	void afterFrame(int pixelCount, unsigned long deltaTime) {
		(void) (pixelCount);

		this->totalDeltaTime += deltaTime;
	}
	void onFrame(struct CRGB * pixel, int pixelIndex, int pixelCount,
			unsigned long deltaTime) {
		(void) (pixelIndex);
		(void) (pixelCount);
		(void) (deltaTime);

		this->currentHue += this->delta;
		(*pixel) = CHSV(this->currentHue, this->hsv.s, this->hsv.v);
	}
};

class ConfettiEffect: public PixelEffect {
private:
	int currentPixel = 0;
	uint8_t hue = 0;
	unsigned long totalDeltaTime = 0;
	float speed = 0.5;
public:
	ConfettiEffect(float speed) :
			PixelEffect(60) {
		this->speed = speed;
	}

	bool beforeFrame(int pixelCount, unsigned long deltaTime) {
		this->currentPixel = random(pixelCount);
		this->totalDeltaTime += deltaTime;
		return true;
	}
	void afterFrame(int pixelCount, unsigned long deltaTime) {
		(void) (pixelCount);
		(void) (deltaTime);

		if (this->totalDeltaTime >= 1000 / this->speed) {
			this->hue++;
		}
	}
	void onFrame(struct CRGB * pixel, int pixelIndex, int pixelCount,
			unsigned long deltaTime) {
		(void) (pixelCount);
		(void) (deltaTime);

		pixel->fadeToBlackBy(10);
		// FIXME new confetti dots are created too fast :-(
		if (pixelIndex == this->currentPixel
				&& this->totalDeltaTime >= 1000 / this->speed) {
			(*pixel) += CHSV(this->hue + random8(64), 200, 255);
		}
	}
};

class SweepEffect: public PixelEffect {
private:
	struct CRGB color;
	int8_t direction = 1;
	float speed = 1;
	float fade = 1;
	bool isBidirectional = false;

	int currentPixel = 0;
	unsigned long totalDeltaTime = 0;

	int movePixel(int currentPosition, int direction, int min, int max) {
		int newPosition = currentPosition + direction;
		if (this->isBidirectional) {
			if (newPosition < min || newPosition >= max) {
				this->direction *= -1;
				newPosition += this->direction;
			}
		} else {
			if (direction < 0 && newPosition < min) {
				newPosition = max - 1;
			} else if (newPosition >= max) {
				newPosition = min;
			}
		}
		return newPosition;
	}

public:
	SweepEffect(struct CRGB color, float speed) :
			PixelEffect(60) {
		this->color = color;
		this->speed = speed;
	}
	bool beforeFrame(int pixelCount, unsigned long deltaTime) {
		(void) (pixelCount);
		this->totalDeltaTime += deltaTime;
		return this->totalDeltaTime > 1000 / this->speed;
	}
	void afterFrame(int pixelCount, unsigned long deltaTime) {
		(void) (deltaTime);
		if (this->totalDeltaTime > 1000 / this->speed) {
			this->currentPixel = movePixel(this->currentPixel, this->direction,
					0, pixelCount);
			this->totalDeltaTime = 0;
		}
	}
	void onFrame(struct CRGB * pixel, int pixelIndex, int pixelCount,
			unsigned long deltaTime) {
		(void) (pixelCount);
		(void) (deltaTime);

		if (pixelIndex == this->currentPixel) {
			pixel->r = this->color.r;
			pixel->g = this->color.g;
			pixel->b = this->color.b;
		} else {
			int r = pixel->r - this->color.r * this->fade;
			int g = pixel->g - this->color.g * this->fade;
			int b = pixel->b - this->color.b * this->fade;
			pixel->r = max(0, r);
			pixel->g = max(0, g);
			pixel->b = max(0, b);
		}
	}
	void setLength(int length) {
		this->fade = 1 / (float) length;
	}
	void setDirection(int8_t direction) {
		this->direction = constrain(direction == 0 ? 1 : direction, -1, 1);
	}
	void setBidirectional(bool state) {
		this->isBidirectional = state;
	}
};

#endif /* LEDEFFECTS_H_ */
