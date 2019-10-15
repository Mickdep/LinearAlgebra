#include "stdafx.h"
#include "CMatrix3d.h"
#include <ostream>
#include <iostream>


CMatrix3d::CMatrix3d()
{
}


CMatrix3d::~CMatrix3d()
{
}

std::shared_ptr<CMatrix3d> CMatrix3d::operator*(std::shared_ptr<CMatrix3d> rhs)
{
	std::shared_ptr<CMatrix3d> result = std::make_shared<CMatrix3d>();
	auto test = rhs->values.size();
	result->values.resize(4);
	for(auto i = 0; i < 4; i++)
	{
		result->values[i].resize(4);
	}
	//Always loop until 4 since our matrix will always be 4x4. The help row is added by defualt since almost all transformations require translations.
	for(auto i = 0; i < 4; i++)
	{
		for(auto j = 0; j < 4; j++)
		{
			auto sum = 0;
			for(auto k = 0; k < 4; k++)
			{
				result->values[i][j] += values[i][k] * rhs->values[k][j];
			}
		}
	}
	return result;                
}