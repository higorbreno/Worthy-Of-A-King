#include "Camera2D.h"

Camera2D::Camera2D()
{
	posX = posY = 0.0f;
}

Camera2D::~Camera2D()
{
}

void Camera2D::MoveTo(float x, float y)
{
	posX = x;
	posY = y;
}

void Camera2D::Translate(float x, float y) {
	posX += x;
	posY += y;
}