/**********************************************************************************
// Vector (Codigo Fonte)
// 
// Criação:     18 Nov 2011
// Atualização: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Classe para representar um vetor
//
**********************************************************************************/

#include "Vector.h"

// ------------------------------------------------------------------------------

const double Vector::PI = 3.1415926535;

// ------------------------------------------------------------------------------

Vector::Vector()
{
    x = 0;
    y = 0;
    angle     = 0;
    magnitude = 0;
}

// ------------------------------------------------------------------------------

void Vector::setXY(float x, float y)
{
    this->x = x;
    this->y = y;
    magnitude = sqrt((x * x) + y * y);
    angle = double(atan2(y, x)) * 180.0f / PI;
}

void Vector::setPolar(float ang, float mag)
{
    this->magnitude = magnitude;
    this->angle = angle;
    x = magnitude * cos(angle * PI / 180.0f);
    y = magnitude * sin(angle * PI / 180.0f);
}

void Vector::Rotate(float theta)
{
    angle -= theta;

    // mantém o ângulo entre 0 e 359 graus
    while (angle < 0 || angle >= 360)
        angle += (angle >= 360 ? -360.0f : 360.0f);
}

// ------------------------------------------------------------------------------

void Vector::Scale(float factor)
{
    magnitude *= factor;
}

// ------------------------------------------------------------------------------

Vector Vector::operator+(const Vector* vector)
{
    Vector result;
    result.setXY(this->x + vector->x, this->y + vector->y);
    return result;
}

// ------------------------------------------------------------------------------

Vector Vector::operator*(float scalar)
{
    Vector result;
    result.setXY(this->x * scalar, this->y * scalar);
    return result;
}

// ------------------------------------------------------------------------------

Vector Vector::operator=(const Vector* vector)
{
    this->setXY(vector->x, vector->y);
    return *this;
}
