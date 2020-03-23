#pragma once
#include "Player.h"

class SceneDrink : public IGameObject
{
public:
	SceneDrink();
	~SceneDrink();
	bool Start();
	void Update();

	//�X�v���C�g�����_���[
	prefab::CSkinModelRender* m_skinModelRenderer = nullptr;

	//�ړ�
	CVector3 m_position = CVector3::Zero;

	Player* player = nullptr;
	//SceneDrink* koop1 = nullptr;
};

