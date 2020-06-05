#pragma once
//#include "ProgressBar.h"
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
	void KanseiCount();

	//�����i�̌���Ԃ�
	int ReturnKanseikosuu()
	{
		return Kansei;
	}
	//�����i�̐�������炷
	void MinusKansei()
	{
		Kansei--;
	}

	//prefab::CSkinModelRender* m_skinModelRender = nullptr;		//�X�L�����f�������_���[�B
private:
	prefab::CSpriteRender* m_spriteRender = nullptr;

	//ProgressBar* Progressbar = nullptr;
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	SceneKaraage* m_karaage = nullptr;
	ScenePoteto* m_poteto = nullptr;
	SceneDrink* m_drink = nullptr;
	SceneMorituke* m_morituke = nullptr;
	SceneAraimono* m_araimono = nullptr;
	SceneKaikei* m_kaikei = nullptr;

	prefab::CFontRender* m_fonttimer = nullptr;
	wchar_t texttimer[256];
	//��������
	float timer = 61.0f;	//�^�C�}�[
	CVector2 timerPos = { 380.0f,280.0f };

	prefab::CFontRender* m_fontkanseihin = nullptr;
	CVector2 kanseiPos = { 380.0f,180.0f };
	int Kansei = 0;
	prefab::CFontRender* m_fontkosuu = nullptr;
	wchar_t textkosuu[256];
	CVector2 kosuuPos = { 550.0f,185.0f };
};

