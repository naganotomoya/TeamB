#pragma once
class ProgressBar :public IGameObject
{
public:
	ProgressBar();
	~ProgressBar();
	bool Start();
	void Update();
private:
	prefab::CSpriteRender* k_spriteRender = nullptr;//唐揚げバー
	prefab::CSpriteRender* p_spriteRender = nullptr;//ポテトバー

	CVector3 k_position = {-580.0,300.0,0.0};//唐揚げバーの位置
	CVector3 p_position = { -580.0,250.0,0.0 };//ポテトバーの位置
	

	CVector3 effecto = { 30.0,160.0,0.0 };//唐揚げエフェ位置
	CVector3 effe = { 70.0,140.0,0.0 };//ポテトエフェ位置

	float x = 1.0f;//赤バー初期値
	float y = 1.0f;//水玉初期値
};

