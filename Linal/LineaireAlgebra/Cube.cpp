#include "stdafx.h"
#include "Cube.h"
#include <SFML/System/Time.hpp>
#include "MatrixFactory.h"


Cube::Cube()
{
	vectors.push_back(CVector3d(300, 100, -2600));		//front top left
	vectors.push_back(CVector3d(300, 100, -2800));		//back top left
	vectors.push_back(CVector3d(500, 100, -2800));		//back top right
	vectors.push_back(CVector3d(500, 100, -2600));		//front top right
	vectors.push_back(CVector3d(300, 300, -2600));		//front bottom left
	vectors.push_back(CVector3d(300, 300, -2800));		//back bottom left
	vectors.push_back(CVector3d(500, 300, -2800));		//back bottom right
	vectors.push_back(CVector3d(500, 300, -2600));		//front bottom right

	indices = {
		0,1,  1,2,  2,3,  3,0,
		0,4,  1,5,  2,6,  3,7,
		4,5,  5,6,  6,7,  7,4
	};

	calculate_center();
}

Cube::~Cube()
{
}

void Cube::pulsate(sf::Time time_elapsed)
{
	const auto translation_matrix_pulse = MatrixFactory::get_translation_matrix_3d(-center_x, -center_y, -center_z);
	const auto inverse_translation_matrix_pulse = MatrixFactory::get_translation_matrix_3d(center_x, center_y, center_z);
	double x_pulse = 1.01;
	double y_pulse = 1.01;
	double z_pulse = 1.01;
	if (static_cast<int>(time_elapsed.asSeconds()) % 2 != 0)
	{
		x_pulse = 1 / 1.01;
		y_pulse = 1 / 1.01;
		z_pulse = 1 / 1.01;
	}
	const auto scale_matrix_pulse = MatrixFactory::get_scale_matrix_3d(x_pulse, y_pulse, z_pulse);
	const auto transformation_matrix_pulse = *inverse_translation_matrix_pulse * (*scale_matrix_pulse * translation_matrix_pulse);

	transform(transformation_matrix_pulse);
}
