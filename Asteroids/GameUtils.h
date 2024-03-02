#pragma once
#include <random>

namespace GameUtils
{
	const float DEGTORAD = 0.01745f;
	const float RADTODEG = 57.2958f;

	static float RandF(const float& min, const float& max);
	static int RandI(const int& min, const int& max);

	static void WrapCoordinates(const float& inputX, const float& inputY, float& outputX, float& outputY, const float& windowWidth, const float& windowHeight, const float& boundingRadius = 0.0f)
	{
		outputX = inputX;
		outputY = inputY;

		if ((outputX + boundingRadius) < 0.0f)			outputX = windowWidth + boundingRadius;
		if ((outputX - boundingRadius) > windowWidth)	outputX = 0.0f - boundingRadius;

		if ((outputY + boundingRadius) < 0.0f)			outputY = windowHeight + boundingRadius;
		if ((outputY - boundingRadius) > windowHeight)	outputY = 0.0f - boundingRadius;
	}

	static bool IsOutsideScreen(const float& inputX, const float& inputY, const float& windowWidth, const float& windowHeight)
	{
		if (inputX < 0.0f || inputX > windowWidth)	return true;
		if (inputY < 0.0f || inputY > windowHeight) return true;

		return false;
	}

	static bool IsInsideScreen(const float& inputX, const float& inputY, const float& windowWidth, const float& windowHeight)
	{
		return ((inputX > 0.0f && inputX < windowWidth) && (inputY > 0.0f && inputY < windowHeight));
	}

	static void SetPosRandomOutsideScreen(float& inputPosX, float& inputPosY, const float& windowWidth, const float& windowHeight)
	{
		float randX = RandF(-windowWidth, windowWidth);
		float randY = RandF(-windowHeight, windowHeight);

		if (randX > 0.0f) randX += windowWidth;
		if (randY > 0.0f) randY += windowHeight;

		inputPosX = randX;
		inputPosY = randY;
	}

	static void GetPosRandomInsideScreen(float& inputPosX, float& inputPosY, const float& windowWidth, const float& windowHeight)
	{
		inputPosX = RandF(windowWidth * 0.1f, windowWidth * 0.9f);
		inputPosY = RandF(windowHeight * 0.1f, windowHeight * 0.9f);
	}

	static float GetBoundingBoxRadius(const float& boundingWidth, const float& boundingHeight)
	{
		const float halfWidth = boundingWidth * 0.5f;
		const float halfHeight = boundingHeight * 0.5f;

		return (halfWidth > halfHeight) ? halfWidth : halfHeight;
	}

	//Returns in Degrees
	static float GetAngle(const float& inputAx, const float& inputAy, const float& inputBx, const float& inputBy)
	{
		float dx = inputBx - inputAx;
		float dy = inputAy - inputBy;

		float angle = std::atan2f(dy, dx);
		angle *= RADTODEG;

		return (angle < 0.0f) ? (360.0f + angle) : angle;
	}

	static float RandF(const float& min, const float& max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(min, max);

		return (float)dis(gen);
	}

	static int RandI(const int& min, const int& max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(min, max);

		return (int)dis(gen);
	}

	static float Lerp(const float& start, const float& end, const float& time)
	{
		return start + (end - start) * time;
	}
}