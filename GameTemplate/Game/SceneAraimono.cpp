#include "stdafx.h"
#include "SceneAraimono.h"
#include "Player.h"
#include "Camera.h"
SceneAraimono::SceneAraimono()
{
}
SceneAraimono::~SceneAraimono()
{
	DeleteGO(m_osara);
}

bool SceneAraimono::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	//お皿
	m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");			//お皿のロード
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);		//90度回転
	m_osara->SetRotation(m_Srotation);
	m_Oposition = { -5110.0f,0.0f,-1.0f };					//初期位置
	m_osara->SetPosition(m_Oposition);

	//汚れ
	m_Yogore = NewGO<prefab::CSpriteRender>(0);
	m_Yogore->Init(L"sprite/Phaikei/Dirt.dds",800.0f,800.0f);//汚れのロード
	m_Yogore->SetPosition(m_YogoPos);						 //初期座標
	return true;
}

void SceneAraimono::Osara()
{
	m_Oposition = m_player->ReturnLPlayerPosition();
	m_Oposition.x += 5.0f;
	m_Oposition.y += 9.0f;
	m_Oposition.z -= 0.5f;
	m_osara->SetPosition(m_Oposition);
}

void SceneAraimono::Update()
{
	Nowscene = m_camera->ReturnNowScene();
	if (Nowscene == 4) {
		Osara();
	}
	
	//左手で持って右手で洗う。
	m_player->LosaraAnime();
	m_player->SetLPosition({ -5110.0f,0.0f,-3.0f });

	//右手とお皿の距離を測る。
	ROdiff = m_player->ReturnRPlayerPosition() - m_Oposition;

	//左手固定の右手のアニメーションであらう？
	//右手のお皿の距離が30以下＆PadのBボタンが押されたらとスティック
	if ( ROdiff.Length()<=30.0 && Pad(0).IsPress(enButtonB)) {
		Araimo += GameTime().GetFrameDeltaTime();
		
	}
	/*if (Araimo % 2==0.0) {

	}*/
	//タイマーが5秒過ぎたら
	if (Araimo >= 5.0) {
		m_osara->SetPosition(KPos);
		KanseiSara++;				//完成皿を増やす。
		Araimo = 0.0f;
	}
	/*ある一定のカウントを超えたらお皿一枚が洗えた。
	次のお皿を初期位置に用意する。&& Pad(0).GetLStickYF()*/
}