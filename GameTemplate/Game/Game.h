#pragma once
#include "ProgressBar.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Player;
class Camera;
class SceneKaraage;
class ScenePoteto;
class SceneDrink;
class SceneMorituke;
class SceneAraimono;
class SceneKaikei;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update()/* override*/;
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;

	ProgressBar* Progressbar = nullptr;
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	SceneKaraage* m_karaage = nullptr;
	ScenePoteto* m_poteto = nullptr;
	SceneDrink* m_drink = nullptr;
	SceneMorituke* m_morituke = nullptr;
	SceneAraimono* m_araimono = nullptr;
	SceneKaikei* m_kaikei = nullptr;
};

