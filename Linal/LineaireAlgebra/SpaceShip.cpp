#include "stdafx.h"
#include "SpaceShip.h"


SpaceShip::SpaceShip()
{
	//These 3 draw the back triangle of the ship. The part you're looking at
	vectors.push_back(CVector3d(100, 100, 0));		//bottom right
	vectors.push_back(CVector3d(0, 100, 0));		//bottom left
	vectors.push_back(CVector3d(50, 25, 0));		//middle top back

	
	vectors.push_back(CVector3d(50, 100, -100));    //middle nose
	vectors.push_back(CVector3d(50, 100, 0));		//middle bottom back
	indices = {
		0,1,  1,2,  2,0, 0,3,  1,3,  4,2,  2,3,
	};

	calculate_center();
}


SpaceShip::~SpaceShip()
{
}

std::shared_ptr<CVector3d> SpaceShip::get_perp()
{
	auto plane_vector1 = vectors[0];
	auto plane_vector2 = vectors[1];
	auto plane_vector3 = vectors[2];
	auto vector1_minus_vector3 = CVector3d(plane_vector1.x - plane_vector3.x, plane_vector1.y - plane_vector3.y, plane_vector1.z - plane_vector3.z);
	auto vector2_minus_vector3 = CVector3d(plane_vector2.x - plane_vector3.x, plane_vector2.y - plane_vector3.y, plane_vector2.z - plane_vector3.z);
	auto perp = vector1_minus_vector3.get_out_product(std::make_shared<CVector3d>(vector2_minus_vector3))->normalize();

	return perp;
}

std::shared_ptr<CVector3d> SpaceShip::get_front()
{
	return std::make_shared<CVector3d>(vectors[3]);
}

std::shared_ptr<CVector3d> SpaceShip::get_back()
{
	return std::make_shared<CVector3d>(vectors[4]);
}

void SpaceShip::add_perpendicular()
{
	auto perpendicular_line = get_perp();
	auto perpendicular_line_final = CVector3d(vectors[3].x + (-perpendicular_line->x * 100), vectors[3].y + (-perpendicular_line->y * 100), vectors[3].z + (-perpendicular_line->z * 100));
	vectors.push_back(perpendicular_line_final);
	indices.push_back(3);
	indices.push_back(5);
}

void SpaceShip::remove_perpendicular()
{
	//Removes the last element, in this case the perpendicular line added.
	vectors.pop_back();
	//Removes the last 2 elements, in this case the indices for the perpendicular line
	indices.pop_back();
	indices.pop_back();
}
