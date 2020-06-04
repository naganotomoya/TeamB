#include "stdafx.h"
#include "SceneDrink.h"
#include "Player.h"
#include "Camera.h"

SceneDrink::SceneDrink()
{
}
SceneDrink::~SceneDrink()
{
	DeleteGO(m_kop);
	DeleteGO(m_kop2);
	DeleteGO(m_db);
	DeleteGO(m_fontRender);
}
bool SceneDrink::Start()
{

	m_camera = FindGO<Camera>("camera");
	//ゴーストの初期化。
	InitGhostObject();

	//モデルをロード
	m_kop = NewGO<prefab::CSkinModelRender>(0, "koop1");
	m_kop->Init(L"modelData/koop1.cmo");
	m_kop->SetPosition(m_position);

	//モデルをロード
	m_kop2 = NewGO<prefab::CSkinModelRender>(0, "koop2");
	m_kop2->Init(L"modelData/koop2.cmo");
	m_kop2->SetPosition(m_position2);
	m_kop2->SetScale({ 1.7f,1.7f,1.7f });

	//アニメーションクリップのロード。
	m_animClips[enAnimationClip_dorinkumizu].Load(L"animData/Drink/waterOut.tka");
	m_animClips[enAnimationClip_kieru].Load(L"animData/Drink/waterEnd2.tka");

	m_animClips[enAnimationClip_dorinkukoora].Load(L"animData/Drink/colaOut.tka");
	m_animClips[enAnimationClip_kierukoora].Load(L"animData/Drink/colaEnd.tka");

	m_animClips[enAnimationClip_dorinkuotya].Load(L"animData/Drink/chaOut.tka");
	m_animClips[enAnimationClip_kieruotya].Load(L"animData/Drink/chaEnd.tka");

	//モデルをロード
	m_db = NewGO<prefab::CSkinModelRender>(0, "dorinkuba");
	m_db->Init(L"modelData/dorinkuba/dorinkuba.cmo", m_animClips, enAnimationClip_Num);
	m_db->SetPosition({ -2560.0f,-10.0f,-30.0f });
	m_db->SetScale({ 0.75f,0.75f,0.75f });




	//ワンショット再生で停止する。
	m_animClips[enAnimationClip_dorinkumizu].SetLoopFlag(false);
	m_animClips[enAnimationClip_dorinkukoora].SetLoopFlag(false);
	m_animClips[enAnimationClip_dorinkuotya].SetLoopFlag(false);
	m_animClips[enAnimationClip_kieru].SetLoopFlag(false);
	m_animClips[enAnimationClip_kierukoora].SetLoopFlag(false);
	m_animClips[enAnimationClip_kieruotya].SetLoopFlag(false);


	m_fontRender = NewGO<prefab::CFontRender>(0);
	m_fontRender2 = NewGO<prefab::CFontRender>(0);
	m_fontRender2->SetColor(m_fontC);

	player = FindGO<Player>("player");
	return true;
}
void SceneDrink::Move()
{
	//コップ1の当たり判定
	m_Pposition = player->ReturnRPlayerPosition();
	//２点間の距離を計算する。
	CVector3 diff1 = m_Pposition - m_position;
	if (diff1.Length() <= 20.0f) {
		if (Pad(0).IsPress(enButtonB)
			&& kophave2 == false) {
			kophave1 = true;
			/*m_position.x = m_Pposition.x;
			m_position.y = m_Pposition.y;*/
			player->Move(m_position);
		}
	}
	//CVector3 diff = player->ReturnRPlayerPosition() - m_position;
	m_kop->SetPosition(m_position);

	//コップ2の当たり判定
	//m_Pposition2 = player->ReturnRPlayerPosition();
	//２点間の距離を計算する。
	CVector3 diff2 = m_Pposition - m_position2;
	if (diff2.Length() <= 20.0f) {
		if (Pad(0).IsPress(enButtonB)
			&& kophave1 == false) {
			kophave2 = true;
			/*m_position.x = m_Pposition.x;
			m_position.y = m_Pposition.y;*/

			player->Move(m_position2);
		}
	}
	//CVector3 diff = player->ReturnRPlayerPosition() - m_position;
	m_kop2->SetPosition(m_position2);
	if (!Pad(0).IsPress(enButtonB)
		&& kophave1 == true) {
		kophave1 = false;
	}
	if (!Pad(0).IsPress(enButtonB)
		&& kophave2 == true) {
		kophave2 = false;
	}

	//２点間の距離を計算する。
	if (timer >= 5.0f) {
		CVector3 diff4 = m_positionG4 - m_position;
		CVector3 diff5 = m_positionG4 - m_position2;
		if (diff4.Length() <= 20.0f || diff5.Length() <= 20.0f) {
			if (!Pad(0).IsPress(enButtonB)) {
				dorinkucount++;
				m_state = Out;
			}
		}
	}


}


void SceneDrink::Animation(CVector3& pos)
{
	CVector3 diff1 = pos - m_positionG3;
	CVector3 diff2 = pos - m_positionG2;
	CVector3 diff3 = pos - m_positionG1;
	CVector3 diff4 = pos - m_positionG4;
//待機状態
	if (m_state == Idle) {
		if (diff1.Length() <= 15.0f
			&& !Pad(0).IsPress(enButtonB)) {
			//アニメーションを再生
			//m_db->PlayAnimation(enAnimationClip_dorinkumizu);
			//水のステートに移動
			m_state = Mizu;
		}
		if (diff2.Length() <= 15.0f
			&& !Pad(0).IsPress(enButtonB)) {
			//アニメーションを再生
			//m_db->PlayAnimation(enAnimationClip_dorinkukoora);
			//コーラのステートに移動
			m_state = Cora;
		}
		if (diff3.Length() <= 15.0f
			&& !Pad(0).IsPress(enButtonB)) {
			//アニメーションを再生
			//m_db->PlayAnimation(enAnimationClip_dorinkuotya);
			//お茶のステートに移動
			m_state = Otya;
			
		}
	}
//水のステート
	if (m_state == Mizu) {
		//ボックスと近ければアニメーション
		if (diff1.Length() <= 15.0f
			&& !Pad(0).IsPress(enButtonB)) {
			//アニメーションを再生
			m_db->PlayAnimation(enAnimationClip_dorinkumizu);
			timer += GameTime().GetFrameDeltaTime();
			dorinkucountsuuzi -= GameTime().GetFrameDeltaTime();
			//5秒で完成（Move）に記述
			if (timer >= 10.0f) {
				//10秒であふれる
				m_state = Out;
			}
		}
	}
//コーラのステート
	if (m_state == Cora) {
		//ボックスと近ければアニメーション
		if (diff2.Length() <= 15.0f
			&& !Pad(0).IsPress(enButtonB)) {
			//アニメーションを再生
			m_db->PlayAnimation(enAnimationClip_dorinkukoora);
			timer += GameTime().GetFrameDeltaTime();
			dorinkucountsuuzi -= GameTime().GetFrameDeltaTime();
			//5秒で完成（Move）に記述
			if (timer >= 10.0f) {
				//10秒であふれる
				m_state = Out;
			}
		}	
	}
//お茶のステート
	if (m_state == Otya) {
		//ボックスと近ければアニメーション
		if (diff3.Length() <= 15.0f
			&& !Pad(0).IsPress(enButtonB)) {
			//アニメーションを再生
			m_db->PlayAnimation(enAnimationClip_dorinkuotya);
			timer += GameTime().GetFrameDeltaTime();
			dorinkucountsuuzi -= GameTime().GetFrameDeltaTime();
			//5秒で完成（Move）に記述
			if (timer >= 10.0f) {
				//10秒であふれる
				m_state = Out;
			}
		}
	}
//溢れたか、完成して元の位置にコップが戻る状態
	if (m_state == Out) {
		m_position = m_Startposition;
		m_position2 = m_Startposition2;
		m_db->PlayAnimation(enAnimationClip_kieru);
		timer = 5.0f;
		dorinkucountsuuzi = 5.0f;
		m_state = Idle;
	}

	//消す
	if (Pad(0).IsTrigger(enButtonRB1) ||
		Pad(0).IsPress(enButtonLB1) ||
		Pad(0).IsPress(enButtonB)) {
		m_db->PlayAnimation(enAnimationClip_kieru);
	}

}

void SceneDrink::Update()
{
	Move();
	Animation(m_position);
	Animation(m_position2);



	//timer += GameTime().GetFrameDeltaTime();

	swprintf_s(text, L"完成品%d個", dorinkucount);
	m_fontRender->SetText(text);
	m_fontRender->SetPosition(m_positiontekisuto);


	//int minute = (int)dorinkucountsuuzi / 60;
	if (m_camera->ReturnNowScene() != 2) {
		m_fontC.w = 0.0f;
		m_fontRender2->SetColor(m_fontC);
	}
	if (m_camera->ReturnNowScene() == 2) {
		m_fontC.w = 1.0f;
		m_fontRender2->SetColor(m_fontC);
	}
	float sec = (int)dorinkucountsuuzi % 60;
	swprintf_s(text2, L"完成まで%02.0f",sec);
	m_fontRender2->SetText(text2);
	m_fontRender2->SetPosition(m_positiontekisuto2);
	m_fontRender2->SetColor(m_fontC);


	//Aボタンが押されたら待機モーションを再生する。
	/*if (Pad(0).IsPress(enButtonA)) {
		m_db->PlayAnimation(enAnimationClip_kieru);
	}*/

	/*if (m_kop) {

		m_position = m_Startposition;
	}*/
	//m_position = m_Startposition;
}

void SceneDrink::InitGhostObject()
{
	//ゴーストのワイヤーフレーム表示を有効にする。
	//PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//ボックス形状のゴーストを作成する。
	//お茶
	m_ghostObject1.CreateBox(
		m_positionG1,	//第一引数は座標。
		CQuaternion::Identity,		//第二引数は回転クォータニオン。
		{ 20.0f, 20.0f, 15.0f }	//第三引数はボックスのサイズ。
	);

	//ボックス形状のゴーストを作成する。
	//コーラ
	m_ghostObject2.CreateBox(
		m_positionG2,	//第一引数は座標。
		CQuaternion::Identity,		//第二引数は回転クォータニオン。
		{ 23.0f, 20.0f, 15.0f }	//第三引数はボックスのサイズ。
	);
	//ボックス形状のゴーストを作成する。
	//水
	m_ghostObject3.CreateBox(
		m_positionG3,	//第一引数は座標。
		CQuaternion::Identity,		//第二引数は回転クォータニオン。
		{ 20.0f, 20.0f, 15.0f }	//第三引数はボックスのサイズ。
	);

	//ボックス形状のゴーストを作成する。
	//完成品
	m_ghostObject4.CreateBox(
		m_positionG4,	//第一引数は座標。
		CQuaternion::Identity,		//第二引数は回転クォータニオン。
		{ 30.0f, 100.0f, 10.0f }	//第三引数はボックスのサイズ。
	);


}