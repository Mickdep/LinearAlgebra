#include "stdafx.h"
#include "GameObject.h"
#include "MatrixFactory.h"


GameObject::GameObject()
{
}


void GameObject::calculate_center()
{
	center_x = 0;
	center_y = 0;
	center_z = 0;
	for (auto i = 0; i < vectors.size(); i++)
	{
		center_x += vectors[i].x / vectors.size();
		center_y += vectors[i].y / vectors.size();
		center_z += vectors[i].z / vectors.size();
	}
}

void GameObject::transform(std::shared_ptr<CMatrix3d> transformation_matrix)
{
	for(auto i = 0; i < vectors.size(); i++)
	{
		std::vector<double> vector_matrix = { vectors[i].x, vectors[i].y, vectors[i].z, vectors[i].w };
		std::vector<double> new_matrix;
		new_matrix.resize(4);
		//Loop through rows
		for (auto row = 0; row < transformation_matrix->values.size(); row++)
		{
			//loop through columns
			for (auto column = 0; column < transformation_matrix->values[row].size(); column++)
			{
				new_matrix[row] += /*floor(*/transformation_matrix->values[row][column] * vector_matrix[column];/* * 100.00) / 100.00;*/
			}
		}
		vectors[i].x = new_matrix[0];
		vectors[i].y = new_matrix[1];
		vectors[i].z = new_matrix[2];
		vectors[i].w = new_matrix[3];
	}
	calculate_center();
}

std::shared_ptr<GameObject> GameObject::clone()
{
	return std::make_shared<GameObject>(*this);
}

void GameObject::rotate_around_axis(std::shared_ptr<CVector3d> axis, double degrees)
{

	//Silly names because: better to read.
	const auto tau1 = atan2(axis->z, axis->x);
	const auto tau2 = atan2(axis->y, sqrt(pow(axis->x, 2) + pow(axis->z, 2)));

	//translate center to origin
	const auto m1 = MatrixFactory::get_translation_matrix_3d(-center_x, -center_y, -center_z);
	//Transleren naar de oorsprong
	const auto m2 = MatrixFactory::get_translation_matrix_3d(-axis->x, -axis->y, -axis->z);
	//breng rotatie as naar x/y vlak. dus roteren met een hoek om de y-as
	const auto m3 = MatrixFactory::get_rotation_matrix_3d_y_axis(tau1);
	//breng rotatie as gelijk met x vlak. dus roteren met een hoek om de z-as
	const auto m4 = MatrixFactory::get_rotation_matrix_3d_z_axis(tau2);
	//Voer rotatie om de as uit
	const auto m5 = MatrixFactory::get_rotation_matrix_3d_x_axis(degrees);
	//breng rotatie terug naar x/y vlak
	const auto m6 = MatrixFactory::get_rotation_matrix_3d_z_axis(-tau2);
	//Terug naar ruimte en startpositie
	const auto m7 = MatrixFactory::get_rotation_matrix_3d_y_axis(-tau1);
	//Transleren terug naar de positie in de ruimte
	const auto m8 = MatrixFactory::get_translation_matrix_3d(axis->x, axis->y, axis->z);
	//translate center back to start position
	const auto m9 = MatrixFactory::get_translation_matrix_3d(center_x, center_y, center_z);

	const auto transformation_matrix = *m9 *(*m8 * (*m7 * (*m6 * (*m5 * (*m4 * (*m3 *(*m2 * m1)))))));

	transform(transformation_matrix);
}

void GameObject::rotate_around_x_axis(double degrees)
{
	//Get the needed matrices
	const auto translation_matrix = MatrixFactory::get_translation_matrix_3d(-center_x, -center_y, -center_z);
	const auto rotation_matrix = MatrixFactory::get_rotation_matrix_3d_x_axis(degrees);
	const auto inverse_translation_matrix = MatrixFactory::get_translation_matrix_3d(center_x, center_y, center_z);

	const auto transformation_matrix = *inverse_translation_matrix * (*rotation_matrix * translation_matrix);

	//Transform
	transform(transformation_matrix);
}

void GameObject::rotate_around_y_axis(double degrees)
{
	const auto translation_matrix = MatrixFactory::get_translation_matrix_3d(-center_x, -center_y, -center_z);
	//Do this calculation because we need to convert the degrees to radians
	const auto rotation_matrix = MatrixFactory::get_rotation_matrix_3d_y_axis(degrees * 0.0174532925);
	const auto inverse_translation_matrix = MatrixFactory::get_translation_matrix_3d(center_x, center_y, center_z);

	const auto transformation_matrix = *inverse_translation_matrix * (*rotation_matrix * translation_matrix);

	transform(transformation_matrix);
}

void GameObject::move_in_direction(std::shared_ptr<CVector3d> direction)
{
	const auto transformation_matrix = MatrixFactory::get_translation_matrix_3d(direction->x * 5, direction->y * 5, direction->z * 5);
	transform(transformation_matrix);
}
