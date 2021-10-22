#ifndef CAMERA_H
#define CAMERA_H

class Camera2D {
private:
	float posX, posY;		// Posições da câmera no mundo

public:
	Camera2D();
	~Camera2D();

	float X() const;	// Retorna posição x da câmera no mundo
	float Y() const;	// Retorna posição y da câmera no mundo

	// Move a câmera para a posição determinada
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