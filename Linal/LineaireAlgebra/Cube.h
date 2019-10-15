#pragma once
#include "CVector3d.h"
#include "GameObject.h"

namespace sf {
	class Time;
}

class Cube : public GameObject
{
public:
	Cube();
	~Cube();
	void pulsate(sf::Time time_elapsed);
};

