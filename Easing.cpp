#include "Easing.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

#include "BaseData.hpp"



Vector2 Easing(Vector2 start, Vector2 end, float volume) {
	return ((start)+((end)-(start)) * (volume));
}


unsigned int ColorEasing(unsigned int statColor, unsigned int endColor, float volume) {
	volume = Clamp(volume, 0.f, 1.f);
	unsigned int redColor = Clamp(Easing<long int>((((statColor & 0xFF000000) >> (4 * 6)) & 0xFF), (((endColor & 0xFF000000) >> (4 * 6)) & 0xFF), volume), 0x00, 0xFF);
	unsigned int greenColor = Clamp(Easing<long int>((((statColor & 0x00FF0000) >> (4 * 4)) & 0xFF), (((endColor & 0x00FF0000) >> (4 * 4)) & 0xFF), volume), 0x00, 0xFF);
	unsigned int blueColor = Clamp(Easing<long int>((((statColor & 0x0000FF00) >> (4 * 2)) & 0xFF), (((endColor & 0x0000FF00) >> (4 * 2)) & 0xFF), volume), 0x00, 0xFF);

	unsigned int alphaColor = Clamp(Easing<long int>((statColor & 0x000000FF), (endColor & 0x000000FF), volume), 0x00, 0xFF);

	return (redColor << (4 * 6)) + (greenColor << (4 * 4)) + (blueColor << (4 * 2)) + (alphaColor);

}

float easeLinear(float number) {
	return number;
}

float easeInBack(float x) {
	const float c1 = 1.70158;
	const float c3 = c1 + 1;

	return c3 * pow(x, 3) - c1 * pow(x, 2);
}

float easeOutBack(float x) {
	const float c1 = 1.70158;
	const float c3 = c1 + 1;

	return 1 + c3 * pow((x)-1, 3) + c1 * pow((x)-1, 2);
}

float easeInCirc(float x) {
	return 1 - sqrt(1 - pow(x, 2));
}

float easeOutCirc(float x) {
	return sqrt(1 - pow(x - 1, 2));
}

float easeInSine(float x) {
	return 1 - cos((x * M_PI) / 2);
}

float easeOutSine(float x) {
	return sin((x * M_PI) / 2);
}

float easeInExpo(float x) {
	return x = (x == 0) ? 0 : pow(2, 10 * x - 10);
}

float easeOutExpo(float x) {
	return x = (x == 1) ? 1 : 1 - pow(2, -10 * x);
}

float easeInQuad(float x) {
	return x * x;
}

float easeOutQuad(float x) {
	return 1 - (1 - x) * (1 - x);
}