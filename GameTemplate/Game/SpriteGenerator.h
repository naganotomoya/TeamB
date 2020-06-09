#pragma once
class SceneKaikei;
class SceneKaraage;
class ScenePoteto;
class SceneMorituke;
class SceneDrink;
class SceneAraimono;
class SpriteGenerator : public IGameObject
{
public:
	SpriteGenerator();
	~SpriteGenerator();
	bool Start();

	void SetPosX();//処理中と待機中の場所を決めた
	void SpriteState();//普通のステート処理
	void KaikeiSyori();//ステート変更の会計時のみ。長いから分けた。
	void NokoriBaa();//バーの処理
	void ColorFade();//次の処理に行く前のフェイド
	void SetKosuu();//それぞれの完成個数を決める。

	//それぞれのチェックマークの処理。もっと簡単な処理とかシラン。
	void CHKara();
	void CHPote();
	void CHYasai();
	//1は水、2はコーラ、3はお茶
	void CHDrink(int num);


	void Update();

private:

	SceneKaraage* m_karaage = nullptr;
	ScenePoteto* m_poteto = nullptr;
	SceneMorituke* m_morituke = nullptr;
	SceneDrink* m_drink = nullptr;
	SceneAraimono* m_araimono = nullptr;
	SceneKaikei* m_kaikei = nullptr;

	prefab::CSpriteRender* m_sprite = nullptr;
	//prefab::CSpriteRender* waku = nullptr;
	prefab::CSpriteRender* baa = nullptr;
	prefab::CSpriteRender* CheckK = nullptr;
	prefab::CSpriteRender* CheckP = nullptr;
	prefab::CSpriteRender* CheckY = nullptr;
	prefab::CSpriteRender* CheckD = nullptr;

	float PosX = 0.0f;

	CVector3 nextScale = { 0.5f,0.5f,0.5f };

	CVector3 StartPos = { -510.0f,230.0f,0.0f };

	CVector4 Fade = { 1.0f,1.0f,1.0f,1.0f };
	bool fade = false;
	int fadeCount = 0;

	CVector3 BaaScale = { 1.0f,1.0f,1.0f };
	float timer = 40.0f;

	bool start = false;
	int setscene = 0;
	int scene = 0;
	int setstate = 0;
	enum State {
		Girl,
		Boy,
		Oldman,
		Fat,
		Kaikei,
		Idle,
		GKaikei,
		BKaikei,
		OKaikei,
		FKaikei,
		NextKaikei,
		DeleteThis
	};
	State m_state = Idle;

	int num = 1;

	int Kara = 0;
	int Pote = num;
	int Yasai = 0;
	int mizu = num;
	int kora = num;
	int otya = num;

	//多分もっと簡単に書けるだろうけど、シラン
	bool SetKara = false;
	bool SetPote = false;
	bool SetYasai = false;
	bool SetDrink = false;
	/*struct Tyuumon
	{
		bool Kara = true;
		bool Pote = true;
		bool Yasai = true;
		bool mizu = false;
		bool kora = false;
		bool otya = false;
	};
	Tyuumon tyuumon[Kaikei];*/

	CVector2 piv = { 0.0f,0.5f };

};

