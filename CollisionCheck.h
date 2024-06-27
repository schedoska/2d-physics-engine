#pragma once

#include <vector>
#include "CollisionData.h"

namespace dm2
{
	struct AxisProjectionData
	{
		AxisProjectionData();
		dm2::Vector closestSecPoint;	/* Secondary object */

		bool isOverlaping;
		float overlapVal;

		dm2::Vector collisionNormal;
	};

	class CollisionCheck
	{
	public:
		static CollisionData check(dm2::ConvexShape* a, dm2::ConvexShape* b);
		static CollisionData check(dm2::ConvexShape* a, dm2::Circle* b);
		static CollisionData check(dm2::Circle* a, dm2::Circle* b);

	private:
		CollisionCheck() {};
		static AxisProjectionData projectOnAxis(dm2::ConvexShape* ref, dm2::ConvexShape* sec, const dm2::Vector& axis);
		static AxisProjectionData projectOnAxis(dm2::ConvexShape* ref, dm2::Circle* sec, const dm2::Vector& axis);
	};
}


