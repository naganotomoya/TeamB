#pragma once
class Player;
class Camera;
class ScenePoteto : public IGameObject
{
public:
	ScenePoteto();
	~ScenePoteto();
	bool Start();
	void PotetoMove(CVector3& pos);
	void Update();
private:
	enum State{
		State_None,				//何もしない状態.
		State_PickPoteto,		//ポテトを取りに行く状態。
		State_TranlateFlyer,	//ポテトをフライヤーまで運ぶ状態。
	};
	State m_state = State_None;
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	prefab::CSkinModelRender* m_Poteto = nullptr;		//ポテトスキンモデル。
	prefab::CSkinModelRender* m_osara = nullptr;		//スキルモデルレンダラー。
	prefab::CSkinModelRender* m_Flyer = nullptr;		//フライヤースキンモデル。
	prefab::CSpriteRender* m_abura = nullptr;		//油の２D


	
	CVector3 Yup = CVector3::Zero;					//プレイヤーのYをちょっと上にしたやつ
	CQuaternion Hanten;								//回転
	CVector3 m_aburaposition = CVector3::Zero;		//油のポジション

	CVector3 m_Fposition = CVector3::Zero;			//フライヤーポジション
	CQuaternion FlyQuater;							//フライやーの回転。
	CVector3 m_Pposition = CVector3::Zero;			//生ポテのポジション
	CVector3 m_Oposition = CVector3::Zero;			//お皿のポジション
	CQuaternion m_Srotation = CQuaternion::Identity;//お皿の回転
	CVector3 PPdiff = CVector3::Zero;				//ポテトとプレイヤーの手の距離

	bool pushPote = false;		//ポテトを持ったか
};

