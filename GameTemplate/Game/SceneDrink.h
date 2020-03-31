#pragma once
#include "Player.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class SceneDrink : public IGameObject
{
public:
	SceneDrink();
	~SceneDrink();
	bool Start();
	void Move();
	void Animation(CVector3& pos);
	void Update();
	void InitGhostObject();

	//スプライトレンダラー
	//prefab::CSkinModelRender* m_skinModelRenderer = nullptr;
	//フォントレンダラー。
	prefab::CFontRender* m_fontRender = nullptr;
	wchar_t text[256];
	CVector2 m_positiontekisuto = { 80.0f,200.0f };
	//CVector3 m_positiontekisuto = { -2580.0f,30.0f};

	//移動
	CVector3 m_position = { -2480.0f,-15.0f,-6.0f };
	CVector3 m_position2 = { -2480.0f,-50.0f,-6.0f };

	CVector3 m_Startposition = { -2480.0f,-20.0f,-6.0f };
	CVector3 m_Startposition2 = { -2480.0f,-50.0f,-6.0f };

	CVector3 m_Pposition = CVector3::Zero;

	CVector3 m_positionG1 = { -2510.0f, -25.0f, -5.0f };
	CVector3 m_positionG2 = { -2553.0f, -25.0f, -5.0f };
	CVector3 m_positionG3 = { -2607.0f, -25.0f, -5.0f };
	CVector3 m_positionG4 = { -2645.0f, -20.0f, -5.0f };

	//スキンモデルレンダラー
	prefab::CSkinModelRender* m_kop = nullptr;
	prefab::CSkinModelRender* m_kop2 = nullptr;
	prefab::CSkinModelRender* m_db = nullptr;


	//移動速度
	//CVector3 m_moveSpeed = CVector3::Zero;

	int m_state = 0;
	int dorinkucount = 0;

	bool kophave1 = false;
	bool kophave2 = false;
	bool Ghave1 = false;
	bool Ghave2 = false;


	Player* player = nullptr;
	//SceneDrink* koop1 = nullptr;

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

};