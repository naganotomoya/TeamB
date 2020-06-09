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
	bool Start();
	void Update();

private:
	SpriteGenerator* m_spriteGene = nullptr;

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


	int num = 1;

	int Kara = num;
	int Pote = num;
	int Yasai = num;
	int mizu = num;
	int kora = num;
	int otya = num;

	bool Yogore = true;

	int KanseiKekka = 0;	//処理したお客さんの人数

	//CVector3 m_position = { -6400.0f,-15.0f,-20.0f };

	////スキンモデルレンダラー
	//prefab::CSkinModelRender* m_hito = nullptr;
};

