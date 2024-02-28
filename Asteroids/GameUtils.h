#pragma once
#include <random>

namespace GameUtils
{
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

	static bool IsOutsideScreen(const float& inputX, const float& inputY, const float& windowWidth, const float& windowHeight)
	{
		if (inputX < 0.0f || inputX > windowWidth) return true;
		if (inputY < 0.0f || inputY > windowHeight) return true;

		return false;
	}

	//Returns in Radians
	static float GetAngle(const float& inputAx, const float& inputAy, const float& inputBx, const float& inputBy)
	{
		float dx = inputBx - inputAx;
		float dy = inputBy - inputAy;

		float angle = std::atan2f(dy, dx);

		return angle;
	}

	static float RandF(const float& min, const float& max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(min, max);

		return (float)dis(gen);
	}
}