/**********************************************************************************
// Vector (Arquivo de Cabe�alho)
// 
// Cria��o:     18 Nov 2011
// Atualiza��o: 13 Out 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Classe para representar um vetor
//
**********************************************************************************/

#ifndef _PROGJOGOS_VECTOR_H_
#define _PROGJOGOS_VECTOR_H_

// --------------------------------------------------------------------------------

#include <cmath>

// --------------------------------------------------------------------------------

class Vector
{
private:
    static const double PI;             // constante PI
    float x, y;
    float angle;                        // �ngulo do vetor com o eixo x
    float magnitude;                    // magnitude do vetor

public:

    Vector();                           // construtor padr�o
    //Vector(float ang, float mag);       // construtor com �ngulo e magnitude

    void setXY(float x, float y);
    void setPolar(float ang, float mag);
    void Rotate(float theta);           // rotaciona vetor por �ngulo em graus
    void Scale(float factor);           // amplia ou reduz vetor por um fator

    float X() const;                    // retorna componente X do vetor
    float Y() const;                    // retorna componente Y do vetor
    float Angle() const;                // retorna componente de angulo do vetor
    float Magnitude() const;            // retorna componente de magnitude do vetor
    float Radians() const;              // retorna �ngulo em radianos

    Vector operator+(const Vector*);    // sobrecarga do operador de soma
    Vector operator*(float);            // sobrecarga do operador de multiplica��o por escalar
    Vector operator=(const Vector*);
}; 

// ---------------------------------------------------------------------------------
// Fun��es Membro Inline

// retorna componente X do vetor
inline float Vector::X() const
{ return x; }    

// retorna componente Y do vetor
inline float Vector::Y() const
{ return y; }    

// retorna componente de angulo do vetor
inline float Vector::Angle() const
{ return angle; }

// retorna componente de magnitude do vetor
inline float Vector::Magnitude() const
{ return magnitude; }

// retorna �ngulo em radianos
inline float Vector::Radians() const
{ return float(angle * PI / 180.0); }

// ------------------------------------------------------------------------------



#endif