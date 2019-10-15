#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet()
{
	//vectors.push_back(CVector3d(200, 100, -30));		//front
	//vectors.push_back(CVector3d(200, 100, 0));		    //back

	indices = {
		0,1
	};
}


Bullet::~Bullet()
{
}
