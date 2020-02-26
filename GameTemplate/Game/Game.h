#pragma once
#include "ProgressBar.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update()/* override*/;
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
private:
	ProgressBar* Progressbar = nullptr;
	prefab::CSpriteRender* m_spriteRender = nullptr;
};

