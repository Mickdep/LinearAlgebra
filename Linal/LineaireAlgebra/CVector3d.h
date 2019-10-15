#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "CMatrix3d.h"

class CVector3d
{
public:
	CVector3d(const double _x, const double _y, const double _z) {
		x = _x; y = _y; z = _z; w = 1;
		//if (!_font.loadFromFile("Roboto-Regular.ttf"))
		//{
		//	std::cout << "Could not load font from file!" << std::endl;
		//}
	};

	CVector3d();
	~CVector3d();

	//sf::Text get_vector_notation() const;

	//sf::Text get_vector_notation() const;

	double x;
	double y;
	double z;
	double w;

	double get_in_product(std::shared_ptr<CVector3d> vector) const;
	std::shared_ptr<CVector3d> get_out_product(std::shared_ptr<CVector3d> vector) const;
	//std::shared_ptr<CVector3d> transform();
	std::shared_ptr<CVector3d> normalize() const;
	void print() const;
private:
	//sf::Font _font;

};

