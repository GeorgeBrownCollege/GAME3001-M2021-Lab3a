#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

//void PlayScene::moveStarShip() const
//{
//	if(m_bToggleSeek)
//	{
//		m_pStarShip->setDesiredVelocity(m_pTarget->getTransform()->position);
//		m_pStarShip->getRigidBody()->velocity = m_pStarShip->getDesiredVelocity();
//		m_pStarShip->getTransform()->position += m_pStarShip->getRigidBody()->velocity;
//	}
//}

void PlayScene::update()
{
	updateDisplayList();

	//moveStarShip();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Add Target to Scene
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(600.0f, 300.0f);
	addChild(m_pTarget);

	// Add StarShip to Scene
	m_pStarShip = new StarShip();
	m_pStarShip->getTransform()->position = glm::vec2(200.0f, 300.0f);
	m_pStarShip->setTargetPosition(m_pTarget->getTransform()->position);
	m_pStarShip->setEnabled(false);
	addChild(m_pStarShip);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME3001 - M2021 - Lab 3", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	/*if(ImGui::Button("Toggle Seek"))
	{
		m_bToggleSeek = !m_bToggleSeek
	}*/

	if(ImGui::Checkbox("Toggle Seek", &m_bToggleSeek))
	{
		m_pStarShip->setEnabled(m_bToggleSeek);
	}


	ImGui::Separator();

	
	
	

	static float speed = m_pStarShip->getMaxSpeed();
	if(ImGui::SliderFloat("Max Speed", &speed, 0.0f, 100.0f))
	{
		m_pStarShip->setMaxSpeed(speed);
	}

	static float acceleration_rate = m_pStarShip->getAccelerationRate();
	if(ImGui::SliderFloat("Acceleration Rate", &acceleration_rate, 0.0f, 50.0f))
	{
		m_pStarShip->setAccelerationRate(acceleration_rate);
	}

	static float turn_rate = m_pStarShip->getTurRate();
	if(ImGui::SliderFloat("Turn Rate", &turn_rate, 0.0f, 20.0f))
	{
		m_pStarShip->setTurnRate(turn_rate);
	}

	ImGui::Separator();
	if (ImGui::Button("Reset"))
	{
		m_pStarShip->getTransform()->position = glm::vec2(200.0f, 300.0f);
		m_pStarShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pStarShip->setCurrentHeading(0.0f); // looking right
		m_pStarShip->setTurnRate(5.0f);
		m_pStarShip->setAccelerationRate(2.0f);
		m_pStarShip->setMaxSpeed(10.0f);
		speed = 10.0f;
		acceleration_rate = 2.0f;
		turn_rate = 5.0f;
		m_pStarShip->setEnabled(false);
		m_bToggleSeek = false;
	}

	
	ImGui::Separator();

	static float target_position[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("Target Position", target_position, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(target_position[0], target_position[1]);
		m_pStarShip->setTargetPosition(m_pTarget->getTransform()->position);
	}
	
	ImGui::End();
}
