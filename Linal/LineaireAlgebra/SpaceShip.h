#pragma once
#include "GameObject.h"

class SpaceShip : public GameObject
{
public:
	SpaceShip();
	~SpaceShip();

	std::shared_ptr<CVector3d> get_perp();
	std::shared_ptr<CVector3d> get_front();
	std::shared_ptr<CVector3d> get_back();
	void add_perpendicular();
	void remove_perpendicular();
};

