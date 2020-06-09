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
	//‚¨‹q‚³‚ñ‚Ì”Ô†
	int KyakuNum()
	{
		return kyakunum;
	}
	//‚¨‹q‚³‚ñ”Ô†‚Ì•ÏX
	void SetKyakuNum();
	void NextTyuumon();
	//‚¨‹q‚³‚ñ‚ğŒ¸‚ç‚·B
	void Setninzuu()
	{
		ninzuu--;
	}
	//¡‚Ìˆ—’†‚Ì‚¨‹q‚³‚ñ
	int NowTyuumon()
	{
		return Nowscene;
	}
	//ƒ‰ƒ“ƒ_ƒ€‚ÅŒˆ’è‚µ‚½‚¨‹q‚³‚ñ
	int RandamuKyaku()
	{
		return Rokyaku;
	}
	//Œ‹‰Ê‚ğ+‚P
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
	//Ÿ‚Ì’•¶‚ª”­¶‚·‚é‚Ü‚Å‚Ì•b”
	float timer = 10.0f;
	//¡‚Ì‚¨‹q‚³‚ñ‚Ìl”
	int ninzuu = 0;
	//‚¨‹q‚³‚ñ‚ğƒ‰ƒ“ƒ_ƒ€‚ÅŒˆ‚ß‚é
	int Rokyaku;
	//Xƒ|ƒWƒVƒ‡ƒ“
	//float PosX = 0.0f;
	//‚¨‹q‚³‚ñ‚Ì”Ô†
	int kyakunum = 0;
	//¡ˆ—‚µ‚Ä‚¢‚é‚¨‹q‚³‚ñ
	int Nowscene = 0;


	int num = 1;

	int Kara = num;
	int Pote = num;
	int Yasai = num;
	int mizu = num;
	int kora = num;
	int otya = num;

	bool Yogore = true;

	int KanseiKekka = 0;	//ˆ—‚µ‚½‚¨‹q‚³‚ñ‚Ìl”

	//CVector3 m_position = { -6400.0f,-15.0f,-20.0f };

	////ƒXƒLƒ“ƒ‚ƒfƒ‹ƒŒƒ“ƒ_ƒ‰[
	//prefab::CSkinModelRender* m_hito = nullptr;
};

