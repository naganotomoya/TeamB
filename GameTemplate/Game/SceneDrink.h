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
	//prefab::CSkinModelRender* m_skinModelRenderer = nullptr;

	//�ړ�
	CVector3 m_position = { -2450.0f,-50.0f,5.0f };
	CVector3 m_Pposition = CVector3::Zero;

	//�X�L�����f�������_���[
	prefab::CSkinModelRender* m_kop = nullptr;	
	prefab::CSkinModelRender* m_db = nullptr;

	
	//�ړ����x
	//CVector3 m_moveSpeed = CVector3::Zero;
	
	int m_state = 0;

	Player* player = nullptr;
	//SceneDrink* koop1 = nullptr;
};