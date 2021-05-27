#include "StarShip.h"
#include "TextureManager.h"
#include "Util.h"
#include <iostream>

StarShip::StarShip()
{
	TextureManager::Instance().load("../Assets/textures/ncl.png", "starship");

	auto size = TextureManager::Instance().getTextureSize("starship");
	setWidth(size.x);
	setHeight(size.y);

	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(AGENT);

	m_maxSpeed = 10.0f; // 10 pixels per frame
	m_turnRate = 5.0f; // 5 degrees per frame
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

void StarShip::setDesiredVelocity(const glm::vec2 target_position)
{
	m_desiredVelocity = Util::normalize(target_position - getTransform()->position) * m_maxSpeed;
	getRigidBody()->velocity = m_desiredVelocity - getRigidBody()->velocity;
	//std::cout << "Desired Velocity: (" << m_desiredVelocity.x << ", " << m_desiredVelocity.y << ")" << std::endl;
}

void StarShip::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void StarShip::setTurnRate(const float angle)
{
	m_turnRate = angle;
}
