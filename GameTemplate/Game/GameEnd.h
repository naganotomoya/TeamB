#pragma once
class GameEnd : public IGameObject
{
public:
	GameEnd();
	~GameEnd();
	bool Start();
	void fontFade();
	void SprintCH();
	void Update();

private:
	float timer = 0.0f;
	CVector2 CenterPivot = { 0.5f,0.5f };
	//Resultのテキスト
	prefab::CFontRender* m_fontkekka = nullptr;
	CVector2 kekkapos = { 0.0f,250.0f };
	//カラッのテキスト
	prefab::CFontRender* m_fontteikyou = nullptr;
	CVector2 teikyoupos = { 200.0f,-50.0f };
	//最終結果
	prefab::CFontRender* m_fontkazu = nullptr;
	wchar_t text[256];
	//数
	CVector2 kazupos = { -100.0f,0.0f };
	int randamu = 0;

	//ここに最終結果を入れる
	int kazu = 0;

	//PressAnyKey
	prefab::CFontRender* m_fontPress = nullptr;
	CVector2 presspos = { -200.0f,-300.0f };
	float fade = 1.0f;
	//int fadecount = 0;
	bool Sfade = true;
	CVector4 colorfont = { 0.0f,0.0f,0.0f,1.0f };

	//画像表示
	enum State {
		Idle,
		Big,
		Big2,
		Sugoi,
		Futuu,
		Kantan
	};
	State m_state = Idle;
	prefab::CSpriteRender* m_hiyoko = nullptr;
	CVector3 hiyokoPos = { 70.0f,-20.0f,0.0f };
	CQuaternion Hanten;
	CVector3 hiyokoScale = { 0.06f,0.07f,0.06f };

};

//class GameEnd
//{
//};
