#pragma once

const float DEGTORAD = 0.01745f;

static void WrapCoordinates(const float& inputX, const float& inputY, float& outputX, float& outputY, const float& windowWidth, const float& windowHeight)
{
	outputX = inputX;
	outputY = inputY;

	if (outputX < 0.0f)			outputX = windowWidth;
	if (outputX > windowWidth)	outputX = 0.0f;

	if (outputY < 0.0f)			outputY = windowHeight;
	if (outputY > windowHeight)	outputY = 0.0f;
}