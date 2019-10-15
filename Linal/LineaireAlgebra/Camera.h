#pragma once
#include "GameObject.h"

class Camera
{
public:
	Camera();
	~Camera();

	void move_forward();
	void move_backwards();
	void rotate_right();
	void rotate_left();
	std::shared_ptr<CMatrix3d> camera_matrix;

private:
	//Executes the translation matrix on the camera
	void move(std::shared_ptr<CMatrix3d> translation_matrix) const;
	void move_look_at(std::shared_ptr<CMatrix3d> translation_matrix) const;

	std::shared_ptr<CVector3d> eye_vector;
	std::shared_ptr<CVector3d> look_at_vector;
	std::shared_ptr<CVector3d> up_vector;
};

