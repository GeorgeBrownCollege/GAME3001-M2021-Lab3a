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

void PlayScene::moveStarShip() const
{
	if(m_bToggleSeek)
	{
		m_pStarShip->setDesiredVelocity(m_pTarget->getTransform()->position);
		m_pStarShip->getRigidBody()->velocity = m_pStarShip->getDesiredVelocity();
		m_pStarShip->getTransform()->position += m_pStarShip->getRigidBody()->velocity;
	}
}

void PlayScene::update()
{
	updateDisplayList();

	moveStarShip();
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
	addChild(m_pStarShip);

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME3001 - M2021 - Lab 2", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	/*if(ImGui::Button("Toggle Seek"))
	{
		m_bToggleSeek = !m_bToggleSeek
	}*/

	ImGui::Checkbox("Toggle Seek", &m_bToggleSeek);

	ImGui::Separator();

	static float target_position[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y};
	if(ImGui::SliderFloat2("Target Position", target_position, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(target_position[0], target_position[1]);
	}
	
	ImGui::End();
}
