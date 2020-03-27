#pragma once
class Camera;
class Player;
class SceneMorituke : public IGameObject
{
public:
	SceneMorituke();
	~SceneMorituke();
	bool Start();
	void Move();
	void Cut();
	void Update();
	int ReturnKyabetuKansei()
	{
		return Kansei;
	}

private:
	Camera* m_camera = nullptr;
	Player* m_player = nullptr;

	prefab::CSkinModelRender* m_kyabetu = nullptr;		//キャベツ
	prefab::CSkinModelRender* m_houtyou = nullptr;		//包丁
	prefab::CSkinModelRender* m_osara = nullptr;		//お皿

	prefab::CSpriteRender* m_manaita = nullptr;			//まな板
	//prefab::CSpriteRender* m_cutkyabetu = nullptr;		//切ったキャベツ
	prefab::CSpriteRender* m_cutOkyabetu = nullptr;		//お皿のキャベツ

	CVector3 m_kyabetupos = { -3830.0f,0.0f,-20.0f };	//キャベツのポジション
	CVector3 m_houtyoupos = { -3800.0f,0.0f,-20.0f };	//包丁のポジション
	CVector3 m_manaitapos = { -3840.0f,0.0f,-50.0f };	//まな板のポジション
	//CVector3 m_cutkyabetupos = { -3854.0f,0.0f,-50.0f };	//切られたキャベツのポジション
	CVector3 m_cutosarakyabetupos = { -3906.5f,4.0f,-10.0f };//お皿に盛られたキャベツのポジション

	CQuaternion m_houtyouRotation = CQuaternion::Identity;//包丁の回転。

	CQuaternion m_Srotation = CQuaternion::Identity;	//お皿の回転。
	CVector3 m_Kscal = CVector3::One;				//キャベツの拡大率
	CVector3 m_Cutscal = { 0.0f, 0.04f, 0.03f };	//切ったキャベツの拡大率
	CVector3 m_CutOsara = { 0.0f,0.0f,1.0f };	//{ 0.01f,0.01f,0.01f }お皿のキャベツの拡大率
	CVector3 KMdiff = CVector3::Zero;				//キャベツとまな板の距離
	CQuaternion Hanten;								//回転

	int nowscene = 0;	//今のシーン
	float CT = 30.0f;	//カットの回数
	int Cutcount = 30;	//連打する回数
	int Kansei = 0;		//完成個数。
};

