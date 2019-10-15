#include "stdafx.h"
#include "Camera.h"
#include "MatrixFactory.h"


Camera::Camera()
{
	//Default values
	eye_vector = std::make_shared<CVector3d>(400, 225, 500);
	look_at_vector = std::make_shared<CVector3d>(400, 300, -500);
	up_vector = std::make_shared<CVector3d>(0, 1, 0);
	camera_matrix = MatrixFactory::get_camera_matrix_3d(eye_vector, look_at_vector, up_vector);

}


Camera::~Camera()
{
}

void Camera::move(std::shared_ptr<CMatrix3d> translation_matrix) const
{
	std::vector<double> vector_matrix = { eye_vector->x, eye_vector->y,eye_vector->z, eye_vector->w };
	std::vector<double> new_matrix;
	new_matrix.resize(4);
	//Loop through rows
	for (auto row = 0; row < translation_matrix->values.size(); row++)
	{
		//loop through columns
		for (auto column = 0; column < translation_matrix->values[row].size(); column++)
		{
			new_matrix[row] += translation_matrix->values[row][column] * vector_matrix[column];
		}
	}
	eye_vector->x = new_matrix[0];
	eye_vector->y = new_matrix[1];
	eye_vector->z = new_matrix[2];
	eye_vector->w = new_matrix[3];
}

void Camera::move_look_at(std::shared_ptr<CMatrix3d> translation_matrix) const
{
	std::vector<double> vector_matrix = { look_at_vector->x, look_at_vector->y, look_at_vector->z, look_at_vector->w };
	std::vector<double> new_matrix;
	new_matrix.resize(4);
	//Loop through rows
	for (auto row = 0; row < translation_matrix->values.size(); row++)
	{
		//loop through columns
		for (auto column = 0; column < translation_matrix->values[row].size(); column++)
		{
			new_matrix[row] += translation_matrix->values[row][column] * vector_matrix[column];
		}
	}
	look_at_vector->x = new_matrix[0];
	look_at_vector->y = new_matrix[1];
	look_at_vector->z = new_matrix[2];
	look_at_vector->w = new_matrix[3];
}

void Camera::move_forward()
{
	//Calculate a vector that goes the direction of the look-at, from the camera.
	const auto vector = std::make_shared<CVector3d>(look_at_vector->x - eye_vector->x, look_at_vector->y - eye_vector->y, look_at_vector->z - eye_vector->z)->normalize();
	//Translate the eye and the look-at forward
	const auto translation_matrix = MatrixFactory::get_translation_matrix_3d(0, 0, 10 * vector->z);
	move(translation_matrix);
	move_look_at(translation_matrix);
	//Update the camera matrix
	camera_matrix = MatrixFactory::get_camera_matrix_3d(eye_vector, look_at_vector, up_vector);
}

void Camera::move_backwards()
{
	//Calculate a vector that goes the direction of the look-at, from the camera.
	const auto vector = std::make_shared<CVector3d>(look_at_vector->x - eye_vector->x, look_at_vector->y - eye_vector->y, look_at_vector->z - eye_vector->z)->normalize();
	//Translate the eye and the look-at forward
	const auto translation_matrix = MatrixFactory::get_translation_matrix_3d(0, 0, -10 * vector->z);
	move(translation_matrix);
	move_look_at(translation_matrix);
	//Update the camera matrix
	camera_matrix = MatrixFactory::get_camera_matrix_3d(eye_vector, look_at_vector, up_vector);
}

void Camera::rotate_right()
{
	//Do classic rotation around point. Translate to that point, rotate, translate back.
	const auto translation_matrix = MatrixFactory::get_translation_matrix_3d(-look_at_vector->x, -look_at_vector->y, -look_at_vector->z);
	const auto rotation_matrix = MatrixFactory::get_rotation_matrix_3d_y_axis(3 * 0.0174532925);
	const auto inverse_translation_matrix = MatrixFactory::get_translation_matrix_3d(look_at_vector->x, look_at_vector->y, look_at_vector->z);
	const auto transformation_matrix = *inverse_translation_matrix * (*rotation_matrix * translation_matrix);
	//Actually move the camera by multiplying it with the transformation matrix
	move(transformation_matrix);
	//Update the camera matrix
	camera_matrix = MatrixFactory::get_camera_matrix_3d(eye_vector, look_at_vector, up_vector);
}

void Camera::rotate_left()
{
	//Do classic rotation around point. Translate to that point, rotate, translate back.
	const auto translation_matrix = MatrixFactory::get_translation_matrix_3d(-look_at_vector->x, -look_at_vector->y, -look_at_vector->z);
	const auto rotation_matrix = MatrixFactory::get_rotation_matrix_3d_y_axis(-3 * 0.0174532925);
	const auto inverse_translation_matrix = MatrixFactory::get_translation_matrix_3d(look_at_vector->x, look_at_vector->y, look_at_vector->z);
	const auto transformation_matrix = *inverse_translation_matrix * (*rotation_matrix * translation_matrix);
	//Actually move the camera by multiplying it with the transformation matrix
	move(transformation_matrix);
	//Update the camera matrix
	camera_matrix = MatrixFactory::get_camera_matrix_3d(eye_vector, look_at_vector, up_vector);
}
