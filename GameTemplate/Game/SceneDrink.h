#pragma once
#include "Player.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class Camera;
class SceneDrink : public IGameObject
{
public:
	SceneDrink();
	~SceneDrink();
	bool Start();
	void Move();
	void Animation(CVector3& pos);
	void Update();
	void MizuUI();
	void InitGhostObject();
	//水の完成を返す
	int ReturnMizu()
	{
		return Kanseimizu;
	}
	//お茶の完成を返す。
	int ReturnOtya()
	{
		return Kanseiotya;
	}
	//コーラの完成を返す
	int ReturnCora()
	{
		return Kanseikora;
	}
	//水の完成をマイナス
	void minusMizu()
	{
		Kanseimizu--;
	}
	//お茶の完成をマイナス
	void minusOtya()
	{
		Kanseiotya--;
	}
	//コーラの完成をマイナス
	void minusCora()
	{
		Kanseikora--;
	}





	//void PostRender(CRenderContext& rc);
private:

	int Kanseimizu = 0;
	int Kanseiotya = 0;
	int Kanseikora = 0;



	prefab::CSoundSource* m_oto = nullptr;

	prefab::CSpriteRender* d_spriteRenderkoppu = nullptr;
	prefab::CSpriteRender* d_spriteRendermizu = nullptr;
	prefab::CSpriteRender* d_spriteRendersutoro = nullptr;
	
	bool toumei = false;

	CQuaternion Hanten = CQuaternion::Identity;
	//CVector3 MizuPos = { -2480.0f,0.0f,0.0f };
	CVector3 MizuPos = { -2560.0f,15.0f,40.0f };
	//CVector3 SC = { 0.05f,0.08f,0.05f };
	CVector3 SC = { 1.2f,1.2f,1.2f };
	CVector3 MizuSpriteScale = { 1.2f,0.0f,1.2f };
	CVector4 mizuclo = { 0.1f,0.0f,0.0f,0.0f };
	bool Clost = false;

	Camera* m_camera = nullptr;
	//スプライトレンダラー
	//prefab::CSkinModelRender* m_skinModelRenderer = nullptr;
	//フォントレンダラー。
	prefab::CFontRender* m_fontRender = nullptr;
	wchar_t text[256];
	prefab::CFontRender* m_fontRender2 = nullptr;
	wchar_t text2[256];
	CVector2 m_positiontekisuto = { 80.0f,200.0f };
	CVector2 m_positiontekisuto2 = { 80.0f,250.0f };
	//CVector3 m_positiontekisuto = { -2580.0f,30.0f};
	CVector4 m_fontC = { 0.0f,0.0f,0.0f,1.0f };

	//移動
	CVector3 m_position = { -2480.0f,-15.0f,-6.0f };
	CVector3 m_position2 = { -2480.0f,-50.0f,-6.0f };

	CVector3 m_Startposition = { -2480.0f,-20.0f,-6.0f };
	CVector3 m_Startposition2 = { -2480.0f,-50.0f,-6.0f };

	CVector3 m_Pposition = CVector3::Zero;

	CVector3 m_positionG1 = { -2510.0f, -25.0f, -5.0f };
	CVector3 m_positionG2 = { -2560.0f, -25.0f, -5.0f };
	CVector3 m_positionG3 = { -2607.0f, -25.0f, -5.0f };
	CVector3 m_positionG4 = { -2645.0f, -20.0f, -5.0f };

	//スキンモデルレンダラー
	prefab::CSkinModelRender* m_kop = nullptr;
	prefab::CSkinModelRender* m_kop2 = nullptr;
	prefab::CSkinModelRender* m_db = nullptr;


	//移動速度
	//CVector3 m_moveSpeed = CVector3::Zero;

	//int m_state = 0;
	int dorinkucount = 0;
	float dorinkucountsuuzi = 5.0f;

	bool kophave1 = false;
	bool kophave2 = false;
	bool Ghave1 = false;
	bool Ghave2 = false;


	Player* player = nullptr;
	//SceneDrink* koop1 = nullptr;

	float timer = 0.0f;


	enum EnAnimationClip {
		enAnimationClip_dorinkumizu, //ドリンクアニメーション
		enAnimationClip_kieru, //ドリンクアニメーション

		enAnimationClip_dorinkukoora,//ドリンクアニメーション
		enAnimationClip_kierukoora, //ドリンクアニメーション


		enAnimationClip_dorinkuotya,//ドリンクアニメーション
		enAnimationClip_kieruotya, //ドリンクアニメーション


		enAnimationClip_Num,	//アニメーションクリップの数。

	};
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CAnimationClip m_animClips[enAnimationClip_Num];	//アニメーションクリップ。

   //ゴーストオブジェクトとを４つ。
	CPhysicsGhostObject m_ghostObject1;	//お茶
	CPhysicsGhostObject m_ghostObject2; //コーラ
	CPhysicsGhostObject m_ghostObject3; //水
	CPhysicsGhostObject m_ghostObject4; //完成品

	enum State {
		Idle,
		Mizu,
		Cora,
		Otya,
		In,
		Out,
		Count,
		End
	};
	State m_state = Idle;

};