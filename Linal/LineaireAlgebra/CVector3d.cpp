#include "stdafx.h"
#include "CVector3d.h"


CVector3d::CVector3d()
{
}

CVector3d::~CVector3d()
{
}

//sf::Text CVector3d::get_vector_notation() const
//{
//	sf::Text text;
//	const std::string vector_notation = "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
//	text.setString(vector_notation);
//	text.setCharacterSize(12);
//	text.setPosition(x, y);
//	text.setFont(_font);
//	return text;
//}

void CVector3d::print() const
{
	std::cout << "Vector(" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl;
}

//Returns the in-product of this and another vector. The in-product is a number.
double CVector3d::get_in_product(const std::shared_ptr<CVector3d> vector) const
{
	return (x * vector->x) + (y * vector->y) + (z * vector->z);
}

//Returns the out-product of this and another vector. The out-product is another vector
std::shared_ptr<CVector3d> CVector3d::get_out_product(const std::shared_ptr<CVector3d> vector) const
{
	auto out_x = (y * vector->z) - (z * vector->y);
	auto out_y = (z * vector->x) - (x * vector->z);
	auto out_z = (x * vector->y) - (y * vector->x);
	return std::make_shared<CVector3d>(out_x, out_y, out_z);
}

std::shared_ptr<CVector3d> CVector3d::normalize() const
{
	const auto x_squared = pow(x, 2);
	const auto y_squared = pow(y, 2);
	const auto z_squared = pow(z, 2);
	const auto length = sqrt(x_squared + y_squared + z_squared);

	auto x_length = x / length;
	auto y_length = y / length;
	auto z_length = z / length;
	return std::make_shared<CVector3d>(x_length, y_length, z_length);
}
