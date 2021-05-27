#include "StarShip.h"
#include "TextureManager.h"
#include "Util.h"
#include <iostream>

#include "Game.h"

StarShip::StarShip()
{
	TextureManager::Instance().load("../Assets/textures/ncl.png", "starship");

	auto size = TextureManager::Instance().getTextureSize("starship");
	setWidth(size.x);
	setHeight(size.y);

	setCurrentHeading(0.0f);
	
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(AGENT);

	m_maxSpeed = 10.0f; // 30 pixels per frame
	m_turnRate = 5.0f; // 5 degrees per frame
	m_accelerationRate = 2.0f; // 1 * by the direction
}

StarShip::~StarShip()
= default;

void StarShip::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the starship
	TextureManager::Instance().draw("starship", x, y, getCurrentHeading(), 255, true);
}

void StarShip::update()
{
	m_move();
}

void StarShip::clean()
{
}

float StarShip::getMaxSpeed() const
{
	return m_maxSpeed;
}

float StarShip::getTurRate() const
{
	return m_turnRate;
}

glm::vec2 StarShip::getDesiredVelocity() const
{
	return m_desiredVelocity;
}

float StarShip::getAccelerationRate() const
{
	return m_accelerationRate;
}

void StarShip::setAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}

void StarShip::setDesiredVelocity(const glm::vec2 target_position)
{
	m_desiredVelocity = Util::normalize(target_position - getTransform()->position) * m_maxSpeed;
	getRigidBody()->velocity = m_desiredVelocity - getRigidBody()->velocity;
	//std::cout << "Desired Velocity: (" << m_desiredVelocity.x << ", " << m_desiredVelocity.y << ")" << std::endl;
}

void StarShip::m_move()
{
	auto deltaTime = TheGame::Instance().getDeltaTime();
	
	// direction with magnitude
	auto target_direction = getTargetPosition() - getTransform()->position;

	// normalized direction
	target_direction = Util::normalize(target_direction);

	// compute the target rotation angle
	auto target_rotation = Util::signedAngle(getCurrentDirection(), target_direction);

	auto turn_sensitivity = 5.0f;
	
	if(abs(target_rotation) > turn_sensitivity)
	{
		if(target_rotation > 0.0f)
		{
			setCurrentHeading(getCurrentHeading() + getTurRate());
		}
		else if (target_rotation < 0.0f)
		{
			setCurrentHeading(getCurrentHeading() - getTurRate());
		}
	}

	getRigidBody()->acceleration = getCurrentDirection() * getAccelerationRate();

	// use the kinematic formula pf = pi + vi * t + 0.5ai * t^2
	getRigidBody()->velocity += getCurrentDirection() * (deltaTime) + 0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, getMaxSpeed());
	
	getTransform()->position += getRigidBody()->velocity;
}

void StarShip::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void StarShip::setTurnRate(const float angle)
{
	m_turnRate = angle;
}
