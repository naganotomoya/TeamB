#include "stdafx.h"
#include "SceneDrink.h"
#include "Player.h"
SceneDrink::SceneDrink()
{
}
SceneDrink::~SceneDrink()
{
	DeleteGO(m_kop);
	DeleteGO(m_kop2);
	DeleteGO(m_db);
}
bool SceneDrink::Start()
{
	//モデルをロード
	m_kop = NewGO<prefab::CSkinModelRender>(0,"koop1");
	m_kop->Init(L"modelData/koop1.cmo");
	m_kop->SetPosition(m_position);

	//モデルをロード
	m_kop2 = NewGO<prefab::CSkinModelRender>(0, "koop2");
	m_kop2->Init(L"modelData/koop2.cmo");
	m_kop2->SetPosition(m_position2);
	m_kop2->SetScale({ 1.5f,1.5f,1.5f });
	//モデルをロード
	m_db = NewGO<prefab::CSkinModelRender>(0, "dorinkuba");
	m_db->Init(L"modelData/dorinkuba2.cmo");
	m_db->SetPosition({ -2560.0f,-40.0f,-30.0f });
	m_db->SetScale({ 0.6f,0.6f,0.6f });


	
	player = FindGO<Player>("player");
	return true;
}
void SceneDrink::Update()
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


}