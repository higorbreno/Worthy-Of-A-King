#ifndef CAMERA_H
#define CAMERA_H

class Camera2D {
private:
	float posX, posY;		// Posi��es da c�mera no mundo

public:
	Camera2D();
	~Camera2D();

	float X() const;	// Retorna posi��o x da c�mera no mundo
	float Y() const;	// Retorna posi��o y da c�mera no mundo

	// Move a c�mera para a posi��o determinada
	void MoveTo(float x, float y);
	void Translate(float x, float y);
};

inline float Camera2D::X() const
{
	return posX;
}

inline float Camera2D::Y() const
{
	return posY;
}


#endif