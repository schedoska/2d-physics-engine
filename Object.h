#pragma once

#include "Vector.h"
#include <vector>
#include <SFML/Graphics.hpp>

namespace dm2
{
	class Object
	{
	public:
		void setPosition(const dm2::Vector& position);
		void setVelocity(const dm2::Vector& velocity);
		void setForce(const dm2::Vector& force);
		void setMass(const float mass);
		void setRotation(const float angle);
		void setAngularVelocity(const float angluarVelocity);
		void setTorque(const float torque);
		void move(const dm2::Vector& vector);
		void setMovable(const bool movable);
		void setRotable(const bool rotable);

		dm2::Vector getPosition() const;
		dm2::Vector getVelocity() const;
		dm2::Vector getForce() const;
		float getMass() const;
		float getRotation() const;
		float getAngularVelocity() const;
		float getTorque() const;
		bool isMovable() const;
		bool isRotable() const;

		virtual void updateMotion(const float dt);
		dm2::Vector localToWorld(const dm2::Vector& vector) const;

	protected:
		Object(const dm2::Vector& position = dm2::Vector());

		dm2::Vector m_position;
		dm2::Vector m_velocity;
		dm2::Vector m_force;
		float m_mass;
		
		float m_rotation;
		float m_angularVelocity;
		float m_torque;

		bool m_movable;
		bool m_rotable;

		// --------------------------------------------------------------------------
		
	public:

		/* EKSPERYMENTALNE BARDZO */
		bool m_constrained;
		Object* m_parent;
		/* EKSPERYMENTALNE BARDZO */

		virtual void draw(sf::RenderWindow& window) = 0;
		virtual void updateDrawableShape() = 0;
	};

	class ConvexShape : public Object
	{
	public:
		ConvexShape(const dm2::Vector& position = dm2::Vector());

		void addVertex(const dm2::Vector& vertex);
		void draw(sf::RenderWindow& window) override;
		void updateDrawableShape() override;
		std::vector<dm2::Vector>& getVerticesList();
		void scaleShape(const float scaleFactor);
		void changeOriginPoint(const dm2::Vector& vector);

	private:
		std::vector<dm2::Vector> m_verticesList;
		sf::ConvexShape m_drawable;
	};

	class Circle : public Object
	{
	public:
		Circle(const dm2::Vector& position = dm2::Vector());
		
		void draw(sf::RenderWindow& window) override;
		void updateDrawableShape() override;
		void setRadius(const float radius);
		float getRadius() const;

	private:
		float m_radius;
		sf::CircleShape m_drawable;
	};
}
