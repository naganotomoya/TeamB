#pragma once
class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	int Scenenum()
	{
		return SceneNum;
	}
	//今のシーンを返す。
	//0からあげ
	//1ポテト
	//2ドリンク
	//3もりつけ
	//4洗い物
	//5会計
	int ReturnNowScene()
	{
		return NowScene;
	}

private:
	struct  Position
	{
		float TxPos;	//ターゲットポジション
		float PxPos;	//カメラポジション
		//int BottonRL;	//どちらのボタンが押されたか・左1・右2
	};
	enum Scene
	{
		Karaage,	//0
		Poteto,		//1
		Drink,		//2
		Morituke,	//3
		Araimono,	//4
		//Kaikei,		//5
		SceneNum
	};

	Position scene[SceneNum];
	//今のシーンの番号
	int NowScene = 0;
	//移動する距離
	float CX = 1280.0f;

	prefab::CSpriteRender* m_spriteKaraage = nullptr;
	prefab::CSpriteRender* m_spritePoteto = nullptr;
	prefab::CSpriteRender* m_spriteDrink = nullptr;
	prefab::CSpriteRender* m_spriteMorituke = nullptr;
	prefab::CSpriteRender* m_spriteAraimono = nullptr;
	//prefab::CSpriteRender* m_spriteKaikei = nullptr;
	CQuaternion Hanten;
	prefab::CDirectionLight* lig = nullptr;
};