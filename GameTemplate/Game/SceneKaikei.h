#pragma once
class SceneKaikei : public IGameObject
{
public:
	SceneKaikei();
	~SceneKaikei();
	bool Start();
	void Update();

	CVector3 m_position = { -6400.0f,-15.0f,-6.0f };

	//�X�L�����f�������_���[
	prefab::CSkinModelRender* m_hito = nullptr;
};

