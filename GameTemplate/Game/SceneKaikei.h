#pragma once
class SpriteGenerator;
class SceneKaraage;
class ScenePoteto;
class SceneMorituke;
class SceneDrink;
class SceneAraimono;
class SceneKaikei : public IGameObject
{
public:
	SceneKaikei();
	~SceneKaikei();
	int NowKyaku()
	{
		return ninzuu;
	}
	//お客さんの番号
	int KyakuNum()
	{
		return kyakunum;
	}
	//お客さん番号の変更
	void SetKyakuNum();
	void NextTyuumon();
	//お客さんを減らす。
	void Setninzuu()
	{
		ninzuu--;
	}
	//今の処理中のお客さん
	int NowTyuumon()
	{
		return Nowscene;
	}
	//ランダムで決定したお客さん
	int RandamuKyaku()
	{
		return Rokyaku;
	}
	//結果を+１
	void KanseiKo()
	{
		KanseiKekka++;
	}
	//結果を返す
	int ReturnKekka()
	{
		return KanseiKekka;
	}
	bool ReturnYogore()
	{
		return Yogore;
	}
	bool Start();
	void Update();
	void YogoreSyori();

private:
	SpriteGenerator* m_spriteGene = nullptr;

	prefab::CSpriteRender* m_spriteYogore = nullptr;

	SceneKaraage* m_karaage = nullptr;
	ScenePoteto* m_poteto = nullptr;
	SceneMorituke* m_morituke = nullptr;
	SceneDrink* m_drink = nullptr;
	SceneAraimono* m_araimono = nullptr;

	/*struct Tyuumon
	{
		bool Karaage;
		bool Poteto;
		bool Drink;
		bool Morituke;
	};
	enum
	{
		kyaku1,
		kyaku2,
		kyakunum
	};

	Tyuumon Kaikei[kyakunum];*/
	//次の注文が発生するまでの秒数
	float timer = 10.0f;
	//汚れ用タイマー
	float Yogoretimer = 0.0f;
	//今のお客さんの人数
	int ninzuu = 0;
	//お客さんをランダムで決める
	int Rokyaku;
	//Xポジション
	//float PosX = 0.0f;
	//お客さんの番号
	int kyakunum = 0;
	//今処理しているお客さん
	int Nowscene = 0;
	//洗い物の数
	int kirei = 0;
	//int karikirei = 0;
	//汚れ用
	int kitanai = 0;
	//int kari = 0;
	float CL = 0.0f;

	int num = 1;

	int Kara = num;
	int Pote = num;
	int Yasai = num;
	int mizu = num;
	int kora = num;
	int otya = num;

	bool Yogore = true;

	int KanseiKekka = 0;	//処理したお客さんの人数

	enum State
	{
		keisann,
		purasu,
		kaeru,
		kitanaine
	};
	State m_state = keisann;

	//CVector3 m_position = { -6400.0f,-15.0f,-20.0f };

	////スキンモデルレンダラー
	//prefab::CSkinModelRender* m_hito = nullptr;
};

