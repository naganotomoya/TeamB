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
	int ReturnPoteto(){			//完成した皿の数を返す
		return KanseiSara;
	}
private:

	enum State {
		State_Nothing,				//何もしない状態.
		State_wash,					//お皿を洗っている状態。
		State_Generate,				//新しくお皿を生成する状態。
	};
	State m_state = State_Nothing;

	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	prefab::CSkinModelRender* m_osara = nullptr;			//お皿のスキンモデル
	CVector3 m_Oposition = CVector3::Zero;					//お皿のポジション
	CQuaternion m_Srotation = CQuaternion::Identity;		//お皿の回転

	prefab::CSpriteRender* m_Yogore = nullptr;				//汚れスキンモデル
	CVector3 m_YogoPos = { -5117.5f,-15.0f,-3.0f };			//汚れのポジション
	CVector3 Scale = { 0.010f, 0.015f, 0.01f };				//
	CQuaternion Hanten;										//回転

	CVector3 KPos = CVector3{ -5070.0f,0.0f,0.0f };			//洗えた皿のポジション	
	CVector3 ROdiff = CVector3::Zero;						//お皿と右手の距離
	float Araimo = 0.0f;									//時間

	float KanseiSara = 0.0;									//洗えたお皿
	int Count = 0;											//時間と何回縮小したか
	int Nowscene = 0;
};

