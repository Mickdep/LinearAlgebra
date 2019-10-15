#pragma once
#include <memory>
#include <vector>

class CMatrix3d
{
public:
	CMatrix3d();
	~CMatrix3d();

	std::vector<std::vector<double>> values;

	std::shared_ptr<CMatrix3d> operator*(std::shared_ptr<CMatrix3d> rhs);
};

