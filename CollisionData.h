#pragma once

#include "Object.h"

namespace dm2
{
	struct CollisionData
	{
		CollisionData(
			bool _collides,
			dm2::Object* _a,
			dm2::Object* _b,
			dm2::Vector _cpA = dm2::Vector(),
			dm2::Vector _cpB = dm2::Vector()
		);

		dm2::Object* objectA;
		dm2::Object* objectB;
		dm2::Vector cpA;
		dm2::Vector cpB;
		bool collides;
	};
}

