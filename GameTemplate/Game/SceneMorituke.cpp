#include "stdafx.h"
#include "SceneMorituke.h"
#include "Camera.h"
#include "Player.h"
SceneMorituke::SceneMorituke()
{
}
SceneMorituke::~SceneMorituke()
{
	DeleteGO(m_kyabetu);
	DeleteGO(m_houtyou);
	DeleteGO(m_manaita);
	DeleteGO(m_cutOkyabetu);
}

bool SceneMorituke::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	//キャベツ
	m_kyabetu = NewGO<prefab::CSkinModelRender>(0, "kyabetu");
	m_kyabetu->Init(L"modelData/MoritukeS/Kyabetu3.cmo");
	m_kyabetu->SetScale(m_Kscal);
	m_kyabetu->SetPosition(m_kyabetupos);
	//包丁
	m_houtyou = NewGO<prefab::CSkinModelRender>(0, "houtyou");
	m_houtyou->Init(L"modelData/MoritukeS/houtyou.cmo");
	m_houtyou->SetPosition(m_houtyoupos);
	m_houtyou->SetScale({ 3.0f,3.0f,3.0f });
	m_houtyouRotation.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_houtyou->SetRotation(m_houtyouRotation);
	//お皿
	m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_osara->SetRotation(m_Srotation);
	m_osara->SetPosition({ -3900.0f,0.0f,-20.0f });
	//まな板
	m_manaita = NewGO<prefab::CSpriteRender>(0);
	m_manaita->Init(
		L"sprite/Phaikei/Manaita.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true	//3D表示
	);
	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//反転
	m_manaita->SetScale({ 0.05f,0.06f,0.05f });
	m_manaita->SetPosition(m_manaitapos);
	m_manaita->SetRotation(Hanten);					//反転を適応
	////切ったキャベツ
	//m_cutkyabetu = NewGO<prefab::CSpriteRender>(0);
	//m_cutkyabetu->Init(
	//	L"sprite/Phaikei/Cutkyabetu.dds",
	//	MainCamera().GetWidth(),
	//	MainCamera().GetHeight(),
	//	true	//3D表示
	//);
	//m_cutkyabetu->SetScale(m_Cutscal);//0.02
	//m_cutkyabetu->SetPosition(m_cutkyabetupos);
	//m_cutkyabetu->SetRotation(Hanten);					//反転を適応
	//m_cutkyabetu->SetPivot({ 1.0f,0.5f });
	//お皿のきゃべつ
	m_cutOkyabetu = NewGO<prefab::CSpriteRender>(0);
	m_cutOkyabetu->Init(
		L"sprite/Karaage/CutKyabetu.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true	//3D表示
	);
	m_cutOkyabetu->SetScale(m_CutOsara);
	m_cutOkyabetu->SetPosition(m_cutosarakyabetupos);
	m_cutOkyabetu->SetRotation(Hanten);					//反転を適応
	m_cutOkyabetu->SetPivot({ 0.5f,0.5f });

	return true;
}

void SceneMorituke::Move()
{
	if (Pad(0).IsTrigger(enButtonB)) {
		m_player->setRHandZ(0.0f);
	}
	//プレイヤーのポジションを使って包丁を動かす。
	m_houtyoupos = m_player->ReturnRPlayerPosition();
	//m_houtyoupos.x +=
	m_houtyoupos.y += 20.0f;
	m_houtyoupos.z -= 5.0f;
	m_houtyou->SetPosition(m_houtyoupos);
}

void SceneMorituke::Cut()
{
	//包丁とまな板の距離が近くて
	//Bボタンを押したら
	KMdiff = m_manaitapos - m_houtyoupos;
	if (KMdiff.Length() <= 50.0f) {
		if (Pad(0).IsTrigger(enButtonB)) {
			//m_player->setRHandZ(0.0f);
			//カットカウントをプラスする。
			Cutcount--;
			//キャベツの拡大率を変える。
			m_Kscal.x -= 1.0f / CT;
			//m_Cutscal.x += 0.02f / CT;
			//お皿に盛られるキャベツの拡大率
			m_CutOsara.x += CutkyabeXScal / (CT / 2);
			m_CutOsara.y += CutkyabeXScal / (CT / 2);
			//キャベツがお皿いっぱいになったら、
			//0にする。
			if (m_CutOsara.x >= CutkyabeXScal ||
				m_CutOsara.y >= CutkyabeXScal) {
				m_CutOsara.x = 0.0f;
				m_CutOsara.y = 0.0f;
				//完成個数を増やす。
				Kansei++;
			}
			//カットカウントが0になったら
			if (Cutcount <= 0) {
				//拡大率を戻す。
				m_Kscal.x = 1.0f;
				//m_Cutscal.x = 0.0f;
				//カットカウントを30にして、
				Cutcount = 30;
			}
		}
		m_kyabetu->SetScale(m_Kscal);
		//m_cutkyabetu->SetScale(m_Cutscal);
		m_cutOkyabetu->SetScale(m_CutOsara);
	}
}

void SceneMorituke::Update()
{
	nowscene = m_camera->ReturnNowScene();
	if (nowscene == 3) {
		m_player->setRHandZ(7.0f);
		m_player->RgripAnimation();
		Move();
		Cut();
	}
	if (Pad(0).IsTrigger(enButtonRB1) ||
		Pad(0).IsTrigger(enButtonLB1)) {
		m_player->setRHandZ(0.0f);
	}
}