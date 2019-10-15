#pragma once
#include <vector>
#include "CMatrix3d.h"
#include "CVector3d.h"

class GameObject
{
public:
	GameObject();
	//Default constructor, this way the subclasses use their own destructor.
	//Enables correct polymorphism
	virtual ~GameObject() = default;

	std::vector<CVector3d> vectors;

	void calculate_center();

	//Define the coordinates of the center of the object
	double center_x;
	double center_y;
	double center_z;

	//List of indices that connect the points, forming vectors.
	std::vector<int> indices;

	//Transforms the object in any way
	void transform(std::shared_ptr<CMatrix3d> transformation_matrix);

	//Clones an object with the exact values
	std::shared_ptr<GameObject> clone();

	void rotate_around_axis(std::shared_ptr<CVector3d> axis, double degrees);

	void rotate_around_x_axis(double degrees);

	void rotate_around_y_axis(double degrees);

	void move_in_direction(std::shared_ptr<CVector3d> direction);

};

