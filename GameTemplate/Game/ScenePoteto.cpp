#include "stdafx.h"
#include "ScenePoteto.h"
#include "Player.h"
#include "Camera.h"

ScenePoteto::ScenePoteto()
{
}

ScenePoteto::~ScenePoteto()
{
	DeleteGO(m_Poteto);
	DeleteGO(m_osara);
}

bool ScenePoteto::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	//ポテト
	m_Poteto = NewGO<prefab::CSkinModelRender>(0, "Poteto");
	m_Poteto->Init(L"modelData/Poteto/poteto.cmo");
	m_Pposition = { -1230.0f,0.0f,0.0f};
	m_Poteto->SetPosition(m_Pposition);
	//フライヤー
	m_Flyer = NewGO<prefab::CSkinModelRender>(1, "Flyer");
	m_Flyer->Init(L"modelData/Poteto/huraiya-4.cmo");
	FlyQuater.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_Flyer->SetRotation(FlyQuater);
	m_Fposition = { -1280.0f,0.0f,-20.0f };
	m_Flyer->SetPosition(m_Fposition);
	//お皿
	m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_osara->SetRotation(m_Srotation);
	m_Oposition = { -1340.0f,0.0f,0.0f };
	m_osara->SetPosition(m_Oposition);

	//油
	//2D表示するときそのままだとでないと思うから3D表示にして反転させてください。
	m_abura = NewGO<prefab::CSpriteRender>(0);
	m_abura->Init(
		L"sprite/Phaikei/Abura.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true	//3D表示
	);
	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//反転
	m_abura->SetScale({ 0.02f,0.0375f,0.05f });
	m_aburaposition = { -1281.5f,14.6f,1.5f };
	m_abura->SetPosition(m_aburaposition);
	m_abura->SetRotation(Hanten);					//反転を適応

	
	
	return true;
}

void ScenePoteto::PotetoMove(CVector3& pos)
{
	PPdiff = m_Pposition - pos;
	//ポテトとプレイヤーの手の距離が近くて、
	//Bボタンが押されているとき。
	//アニメーション追加した時にその処理も追加
	//アニメーションが再生されている時という処理追加したら
	//閉じるときしかつかめないように出来るはず。
	if (PPdiff.Length() <= 8.0f &&
		Pad(0).IsPress(enButtonB)) {
		if (pushPote == false) {
			pushPote = true;
		}
		//m_player->Move()はプレイヤークラスに定義宣言
		//プレイヤーと同じ動きをする。
		//引数に好きな変数を入れたらどこでも使える。
		if (pushPote == true) {
			m_player->Move(pos);
		}
	}
}

void ScenePoteto::Update()
{
	if (m_state == State_None) {
		if (Pad(0).IsPress(enButtonB)) {
			m_state = State_PickPoteto;
		}
	}
	else if (m_state == State_PickPoteto) {
		//②手とポテトの距離が近くなったら、
		PPdiff = m_player->ReturnRPlayerPosition() - m_Pposition;
		if (PPdiff.Length() <= 30.0f &&
			Pad(0).IsPress(enButtonB)) {
			/*Yup = m_player->ReturnRPlayerPosition();
			Yup.y += 15.0f;
			m_Poteto->SetPosition(Yup);*/
			m_player->Move(m_Pposition);
			//m_state = State_TranlateFlyer;
		}
	}
	else if (m_state == State_TranlateFlyer) {

	}
	m_Poteto->SetPosition(m_Pposition);
}