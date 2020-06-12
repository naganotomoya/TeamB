#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start() override;
	void TaxtMove();
	void volup();
	void Update() override;
	//prefab::CSpriteRender* m_spriteRender = nullptr;
private:
	prefab::CFontRender* m_fontAgekire = nullptr;
	prefab::CFontRender* m_fontKaraage = nullptr;
	prefab::CFontRender* m_Press = nullptr;


	CVector3 AKcolor = { 0.95f,0.5f,0.2f };
	//あげきれの移動に使う変数
	float MoveY = 0.0f;
	CVector2 AgekirePos = { -1000.0f,200.0f };
	int Bundnum = 0;
	enum AState {
		Down,
		Up,
		Stop
	};
	AState m_Astate = Down;

	//からあげ！の移動に使う変数
	float karaageS = 0.0f;
	CVector2 KaraagePos = { -400.0f,-100.0f };
	float Kscal = 0.0f;
	enum KState {
		Idle,
		Big,
		Small,
		KStop
	};
	KState m_Kstate = Idle;

	//Pressaに使う変数
	CVector4 color = { 0.0f,0.0f,0.0f,1.0f };
	enum PState {
		PIdle,
		in,
		out
	};
	PState m_Pstate = PIdle;

	//wchar_t texttimer[256];
	prefab::CSoundSource* m_age = nullptr;
	float vol = 0.0f;
};
