#pragma once

#include "CollisionCheck.h"

namespace dm2
{
	class CollisionSolution
	{
	public:
		static void solveCollision(dm2::CollisionData &collisionData);

	private:
		CollisionSolution() {};
	};
}


