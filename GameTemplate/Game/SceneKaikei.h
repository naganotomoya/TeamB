#pragma once
class SceneKaikei : public IGameObject
{
public:
	SceneKaikei();
	~SceneKaikei();
	bool Start();
	void Update();

	CVector3 m_position = { -6400.0f,-15.0f,-6.0f };

	//スキンモデルレンダラー
	prefab::CSkinModelRender* m_hito = nullptr;
};

