#pragma once
class Player;
class Camera;
class ScenePoteto : public IGameObject
{
public:
	ScenePoteto();
	~ScenePoteto();
	bool Start();
	void Update();
	float ReturnPotetoTime() {		//ポテトを揚げている秒数
		return PoteFly;
	}
	int ReturnKanseiPoteto() {		//ポテト完成の変数
		return PotetoKansei;
	}
	void SetPotetoKosuu() {			//ポテトの個数をマイナス
		PotetoKansei--;
	}
private:
	enum State{
		State_None,				//何もしない状態.
		State_PickPoteto,		//ポテトを運んでいる状態。
		State_TranlateFlyer,	//ポテトをお皿に盛り付ける状態。
		State_oilinput,			//油の中に入っている状態。
	};
	State m_state = State_None;
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	prefab::CSkinModelRender* m_Poteto = nullptr;		//生ポテトスキンモデル。
	prefab::CSkinModelRender* m_KanseiPoteto = nullptr; //ポテトスキンモデル。
	prefab::CSkinModelRender* m_osara = nullptr;		//スキルモデルレンダラー。
	prefab::CSkinModelRender* m_Flyer = nullptr;		//フライヤースキンモデル。
	prefab::CSpriteRender* m_abura = nullptr;		//油の２D


	
	
	CQuaternion Hanten;								//回転
	CVector3 m_aburaposition = CVector3::Zero;		//油のポジション

	CVector3 m_Fposition = CVector3::Zero;			//フライヤーポジション
	CQuaternion FlyQuater;							//フライヤーの回転。
	
	CVector3 m_Pposition = CVector3::Zero;			//生ポテのポジション
	CVector3 InitialPosition = { -1208.0f,0.0f,0.0f };//生ポテ初期位置
	CVector3 m_Kanseiposition = { -1230.0f,0.0f,-300.0f };		//完成ポテトのポジション
	CVector3 m_Oposition = CVector3::Zero;			//お皿のポジション
	CQuaternion m_Srotation = CQuaternion::Identity;//お皿の回転

	CVector3 PPdiff = CVector3::Zero;				//ポテトとプレイヤーの手の距離
	CVector3 PTdiff = CVector3::Zero;				//ポテトと皿の距離
	CVector3 APdiff = CVector3::Zero;				//油とポテトの距離

	float PoteFly = 0.0;							//ポテトを揚げる秒数
	int PotetoKansei = 0;							//完成したポテトの数
	bool Nama = true;								//生があるか
	bool Fried = false;								//揚げたポテトがあるか
	int nowscene = 0;

};

