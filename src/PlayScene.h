#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "StarShip.h"
#include "Target.h"


class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	void moveStarShip() const;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	// Game Objects
	Target* m_pTarget;
	StarShip* m_pStarShip;

	// UI Controls
	bool m_bToggleSeek;
};

#endif /* defined (__PLAY_SCENE__) */