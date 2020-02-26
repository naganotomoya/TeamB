#pragma once
class ProgressBar :public IGameObject
{
public:
	ProgressBar();
	~ProgressBar();
	bool Start();
	void Update();
private:
	prefab::CSpriteRender* k_spriteRender = nullptr;
	CVector3 k_position = {0.0,0.0,0.0};
	float x = 0.0f;
};

