#pragma once
class Player;
class Camera;
class SceneAraimono : public IGameObject
{
public:
	SceneAraimono();
	~SceneAraimono();
	bool Start();
	void Osara();
	void Update();
private:
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	prefab::CSkinModelRender* m_osara = nullptr;			//お皿のスキンモデル
	CVector3 m_Oposition = CVector3::Zero;					//お皿のポジション
	CQuaternion m_Srotation = CQuaternion::Identity;		//お皿の回転

	prefab::CSpriteRender* m_Yogore = nullptr;				//汚れスキンモデル
	CVector3 m_YogoPos = { -5110.0f,0.0f,0.0f };			//汚れのポジション

	CVector3 KPos = CVector3{ -5070.0f,0.0f,0.0f };			//洗えた皿のポジション	
	CVector3 ROdiff = CVector3::Zero;						//お皿と右手の距離
	float Araimo = 0.0f;										//時間

	float KanseiSara = 0.0;									//洗えたお皿
	int Nowscene = 0;
};

