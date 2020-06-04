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
	m_Oposition = { -5105.0f,-20.0f,-5.0f };					//初期位置
	m_osara->SetPosition(m_Oposition);

	//汚れ
	m_Yogore = NewGO<prefab::CSpriteRender>(0);
	m_Yogore->Init(L"sprite/Phaikei/Dirt.dds", MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true);//汚れのロード
	

	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//反転
	m_Yogore->SetScale(Scale);
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
	m_player->SetLPosition({ -5110.0f,-23.0f,-10.0f });

	//右手とお皿の距離を測る。
	ROdiff = m_player->ReturnRPlayerPosition() - m_Oposition;

	//タイマー的存在
	Araimo += GameTime().GetFrameDeltaTime();

	//左手固定の右手のアニメーションであらう？
	//右手のお皿の距離が30以下＆PadのBボタンが押されたらとスティック
	if (ROdiff.Length() <= 20.0 && Pad(0).IsPress(enButtonB) && m_state != State_Generate) {
		//お皿を洗っている状態に変える
		m_state = State_wash;
		
		//1秒経過するたびにちいさくして最終消す。
		if (Araimo >= 1.0f && Count != 3 ) {
			//汚れのスケールをyogere_scaleに持ってくる
			CVector3 yogere_scale = m_Yogore->GetScale();
			yogere_scale.x /= 2;
			yogere_scale.y /= 2;

			m_Yogore->SetScale(yogere_scale);
			
			Araimo = 0.0f;
			Count++;
		}
			//タイマーが5秒過ぎたら
		if (Count == 3 ) {
			DeleteGO(m_Yogore);						//汚れを消す
			m_osara->SetPosition(KPos);				//お皿を他の位置に移動させる。
			KanseiSara++;				            //完成皿を増やす。
			Araimo = 0.0f;							//洗い物のタイマを0.0にする
			Count = 0;								//縮小する数の初期化
			m_state = State_Generate;				//お皿を生成する状態
		}
	}

	if (m_state == State_Generate) {
		//お皿を移動する状態
		if (Araimo >= 2.0) {						//2秒たったら
			//お皿のポジションを移動
			m_osara->SetPosition(m_Oposition);
			//汚れを生成する
			m_Yogore = NewGO<prefab::CSpriteRender>(0);
			m_Yogore->Init(L"sprite/Phaikei/Dirt.dds", MainCamera().GetWidth(),
				MainCamera().GetHeight(),
				true);//汚れのロード


			Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//反転
			m_Yogore->SetScale(Scale);
			m_Yogore->SetPosition(m_YogoPos);
			m_Yogore->SetRotation(Hanten);					//反転を適応
			m_state = State_Nothing;				//何もしていない状態
		}
	}
	

	/*m_stateがState_washにはいってる
	洗い終わった後にあの辺でｂ押したらまたState_washに入る*/
}