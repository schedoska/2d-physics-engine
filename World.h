#pragma once

#include <vector>
#include "Object.h"

namespace dm2 
{
	class World
	{
	public:
		World();

		void addObject(dm2::ConvexShape* object);
		void addObject(dm2::Circle* object);

		void updateAll(float dt);
		void drawAll(sf::RenderWindow &window);
		void resolveCollisions(sf::RenderWindow& window);

	private:
		std::vector<dm2::Object*> m_objectList;
		std::vector<dm2::ConvexShape*> m_convexShapeList;
		std::vector<dm2::Circle*> m_circleList;
	};
}

