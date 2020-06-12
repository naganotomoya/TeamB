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
	DeleteGO(m_KanseiPoteto);
	DeleteGO(m_Flyer);
	DeleteGO(m_osara);
	DeleteGO(m_abura);
	//DeleteGO(piyo);
}

bool ScenePoteto::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	//生ポテト
	m_Poteto = NewGO<prefab::CSkinModelRender>(0, "Poteto");
	m_Poteto->Init(L"modelData/icePote/Poteto1.cmo");
	m_Pposition = { -1208.0f,0.0f,0.0f};
	m_Poteto->SetPosition(m_Pposition);
	//ポテト
	m_KanseiPoteto = NewGO<prefab::CSkinModelRender>(0, "KanseiPoteto");
	m_KanseiPoteto->Init(L"modelData/Poteto/poteto.cmo");
	m_KanseiPoteto->SetPosition(m_Kanseiposition);
	
	//フライヤー
	m_Flyer = NewGO<prefab::CSkinModelRender>(1, "Flyer");
	m_Flyer->Init(L"modelData/Poteto/huraiya-4.cmo");
	FlyQuater.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_Flyer->SetRotation(FlyQuater);
	m_Flyer->SetScale({ 1.5f,1.25f,1.25f });
	m_Fposition = { -1275.0f,-20.0f,-30.0f };
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
	m_abura->SetScale({ 0.031f,0.05f,0.05f });
	m_aburaposition = { -1278.0f,4.0f,-5.0f };
	m_abura->SetPosition(m_aburaposition);
	m_abura->SetRotation(Hanten);					//反転を適応


	piyo = NewGO<prefab::CSoundSource>(0);
	piyo->Init(L"sound/SE/age.wav");
	piyo->Play(true);
	piyo->SetVolume(0.0f);
	
	return true;
}


void ScenePoteto::Update()
{
	PoteFly += GameTime().GetFrameDeltaTime();//お時間です。
	nowscene = m_camera->ReturnNowScene();
	if (nowscene == 1) {
		//Bを押している間手を閉じたい場合の処理
		if (Pad(0).IsPress(enButtonB)) {
			m_player->RgripAnimation();//閉じる
		}
		else {
			m_player->RopenAnimation();//開く
		}
	}

	//なにもない状態
	if (m_state == State_None) {
		if (Pad(0).IsPress(enButtonB)) {
			m_state = State_PickPoteto;
		}
	}

	//ポテトを持っている状態
	else if (m_state == State_PickPoteto) {
		//プレイヤーの手とポテトの距離を測定
		PPdiff = m_player->ReturnRPlayerPosition() - m_Pposition;
		//プレイヤーの手の当たり判定計算
		float len = PPdiff.Length();
		//距離３０以下でBボタンが押されたら
		if (len <= 30.0f && Pad(0).IsPress(enButtonB)) {
			m_player->Move(m_Pposition);
			if (Nama == true) {
				m_Poteto->SetPosition(m_Pposition);
			}
			else {
				m_KanseiPoteto->SetPosition(m_Pposition);

			}
			
		}

		//ポテトとお皿の距離が近くなったら
		PTdiff = m_Pposition - m_Oposition;
		//当たり判定
		len = PTdiff.Length();

		//ポテトと油の距離が近くなったら
		APdiff = m_Pposition - m_aburaposition;
		//当たり判定
		float Len = APdiff.Length();

		//IsActive()はDeleteGOされたらFalse　NewGOされたらTrueなるフラグ
		if (len <= 20.0f && !Pad(0).IsPress(enButtonB) && m_KanseiPoteto->IsActive() == true) {
			bool Ispoteto = true;
			//お皿とポテトの距離が20.0以下でBボタンが押されてなくて、ポテトのアクティブがTrueなら
			m_state = State_TranlateFlyer;
		}

		//ポテトと油の距離が近くなったら揚げている状態にループ
		else if (Len <= 20.0f && !Pad(0).IsPress(enButtonB) && m_Poteto->IsActive() == true) {
			PoteFly = 0.0f;
			m_state = State_oilinput;
		}
	
	}

	//ポテトを揚げている状態
	else if (m_state == State_oilinput) {
		//揚げているときにBGM
		piyo->SetVolume(1.0f);
		if (PoteFly >= 1 ) {
			//生ポテとを削除する。
			//DeleteGO(m_Poteto);
			m_Poteto->SetScale({ 0.0f,0.0f,0.0f });
			Nama = false;				//生のポテトがなくなった.
			//揚げたてポテトを生成
			//m_KanseiPoteto = NewGO<prefab::CSkinModelRender>(0, "KanseiPoteto");
			//m_KanseiPoteto->Init(L"modelData/Poteto/poteto.cmo");
			m_KanseiPoteto->SetScale({ 1.0f,1.0f,1.0f });
			Fried = true;				//ポテトがあるよ。
			//揚げたてポテトをNewGOする
			m_KanseiPoteto->SetPosition(m_Pposition);
			//揚げたポテトを持ちたい
			m_state = State_None;
		}
	}

	//ポテトを盛り付ける状態
	else if (m_state == State_TranlateFlyer) {
		piyo->SetVolume(0.0f);
		//ステートが盛り付ける状態なら
		//ポテトのオブジェクトを削除
		//DeleteGO(m_KanseiPoteto);
		m_KanseiPoteto->SetScale({ 0.0f,0.0f,0.0f });
		//生ポテトを生成
		//m_Poteto = NewGO<prefab::CSkinModelRender>(0, "Poteto");
		//m_Poteto->Init(L"modelData/icePote/Poteto1.cmo");

		//完成したポテとの数
		PotetoKansei++;

		m_Poteto->SetScale({ 1.0f,1.0f,1.0f });
		m_Pposition = InitialPosition;
		m_Poteto->SetPosition(m_Pposition);
		Nama = true;				//生のポテトがある。
		//ステートを何もしてない状態に変更
		m_state = State_None;
	}

}