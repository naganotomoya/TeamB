#pragma once
class ProgressBar :public IGameObject
{
public:
	ProgressBar();
	~ProgressBar();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc);
private:
	prefab::CSpriteRender* k_spriteRender = nullptr;//唐揚げバー
	prefab::CSpriteRender* p_spriteRender = nullptr;//ポテトバー
	prefab::CSpriteRender* waku = nullptr;//枠
	prefab::CSpriteRender* waku_01 = nullptr;//枠

	CVector3 k_position = {-580.0,300.0,0.0};//唐揚げバーの位置
	CVector3 p_position = { -580.0,230.0,0.0 };//ポテトバーの位置
	CVector3 w_position = { -340.0,300.0,0.0 };//枠の位置
	CVector3 w01_position = { -340.0,230.0,0.0 };//枠の位置
	

	CVector3 effecto = { 15.0,50.0,0.0 };//唐揚げエフェ位置
	CVector3 effe = { 10.0,30.0,0.0 };//ポテトエフェ位置

	float x = 1.0f;//赤バー初期値
	float y = 1.0f;//水玉初期値

	CFont m_font;
	int k = 0.0, p = 0.0;
};

