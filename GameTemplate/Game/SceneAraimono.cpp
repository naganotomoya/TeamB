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
	DeleteGO(m_Yogore);
}

bool SceneAraimono::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	//お皿
	m_osara = NewGO<prefab::CSkinModelRender>(1, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");			//お皿のロード
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);		//90度回転
	m_osara->SetRotation(m_Srotation);
	m_Oposition = { -5105.0f,-20.0f,-1.0f };					//初期位置
	m_osara->SetPosition(m_Oposition);

	//汚れ
	m_Yogore = NewGO<prefab::CSpriteRender>(0);
	m_Yogore->Init(L"sprite/Phaikei/Dirt.dds", MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true);//汚れのロード
	

	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//反転
	m_Yogore->SetScale({ 0.010f,0.015f,0.01f });
	m_Yogore->SetPosition(m_YogoPos);
	m_Yogore->SetRotation(Hanten);					//反転を適応

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
		//Osara();
	}

	//左手で持って右手で洗う。
	m_player->LosaraAnime();
	//左手の手の位置
	m_player->SetLPosition({ -5110.0f,-23.0f,-2.0f });

	//右手とお皿の距離を測る。
	ROdiff = m_player->ReturnRPlayerPosition() - m_Oposition;

	//左手固定の右手のアニメーションであらう？
	//右手のお皿の距離が30以下＆PadのBボタンが押されたらとスティック
	if (ROdiff.Length() <= 30.0 && Pad(0).IsPress(enButtonB)) {
		Araimo += GameTime().GetFrameDeltaTime();
		//1秒経過するたびにちいさくして最終消す。
	}
	
	//タイマーが5秒過ぎたら
	if (Araimo >= 5.0) {
		DeleteGO(m_Yogore);						//汚れを消す
		m_osara->SetPosition(KPos);				//お皿を他の位置に移動させる。
		KanseiSara++;				            //完成皿を増やす。
		Araimo = 0.0f;							//洗い物のタイマを0.0にする
	}
	/*ある一定のカウントを超えたらお皿一枚が洗えた。
	次のお皿を初期位置に用意する。&& Pad(0).GetLStickYF()*/
}