#include "stdafx.h"
#include "SceneAraimono.h"
#include "Player.h"
SceneAraimono::SceneAraimono()
{
}
SceneAraimono::~SceneAraimono()
{
	DeleteGO(m_osara);
}

bool SceneAraimono::Start()
{
	m_player = FindGO<Player>("player");
	//お皿
	m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");//お皿のロード
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);//90度回転
	m_osara->SetRotation(m_Srotation);
	m_Oposition = { -5110.0f,0.0f,0.0f };			  //初期位置
	m_osara->SetPosition(m_Oposition);
	return true;
}

void SceneAraimono::Update()
{
	//左手で持って右手で洗う。
	//左手固定の右手のアニメーションであらう？
	if (Pad(0).IsPress(enButtonB) && Pad(0).GetLStickYF()) {
		//お皿を洗う。

	}
}