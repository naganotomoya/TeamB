#pragma once
#include "Player.h"

class SceneDrink : public IGameObject
{
public:
	SceneDrink();
	~SceneDrink();
	bool Start();
	void Update();

	//スプライトレンダラー
	prefab::CSkinModelRender* m_skinModelRenderer = nullptr;

	//移動
	CVector3 m_position = CVector3::Zero;

	Player* player = nullptr;
	//SceneDrink* koop1 = nullptr;
};

