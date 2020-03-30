#include "stdafx.h"
#include "SceneKaraage.h"
#include "Player.h"
#include "Camera.h"

SceneKaraage::SceneKaraage()
{

}
SceneKaraage::~SceneKaraage()
{
	DeleteGO(m_tong);
	DeleteGO(m_nama);
	DeleteGO(m_abura);
	DeleteGO(m_osara);
	DeleteGO(m_kansei);

}

bool SceneKaraage::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	//トング
	m_tong = NewGO<prefab::CSkinModelRender>(0, "tong");
	m_tong->Init(L"modelData/tongs.cmo");
	//モデル調整したら下のは多分いらない。
	m_Trotation.SetRotationDeg(CVector3::AxisX, 180.0f);
	m_tong->SetRotation(m_Trotation);
	m_tong->SetScale({ 2.0f,2.0f,2.0f });
	//生のからあげ
	m_nama = NewGO<prefab::CSkinModelRender>(0, "nama");
	m_nama->Init(L"modelData/KaraageS/Nama.cmo");
	m_Kposition = { 74.0f,0.0f,-5.0f };
	m_StartPos = m_Kposition;
	m_nama->SetPosition(m_Kposition);
	//お皿
	m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_osara->SetRotation(m_Srotation);
	m_Sposition = { -60.0f,0.0f,-10.0f };
	m_osara->SetPosition(m_Sposition);

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
	m_abura->SetScale({ 0.05f,0.1f,0.05f });
	m_aburaposition = { -10.0f,0.0f,-20.0f };
	m_abura->SetPosition(m_aburaposition);
	m_abura->SetRotation(Hanten);					//反転を適応
	//完成したからあげ
	m_kansei = NewGO<prefab::CSkinModelRender>(0, "kansei");
	m_kansei->Init(L"modelData/KaraageS/Kansei.cmo");
	m_Knseiposition = m_KnseiStartposition;
	m_kansei->SetPosition(m_Knseiposition);

	//m_fontkansei = NewGO<prefab::CFontRender>(0);


	return true;
}

void SceneKaraage::TongMove()
{
	//プレイヤーのポジションを使って
	//トングのポジションにする
	m_Tposition = m_player->ReturnRPlayerPosition();
	m_Tposition.x += 2.0f;
	m_Tposition.y += 25.0f;
	m_Tposition.z += -3.0f;
	m_tong->SetPosition(m_Tposition);
}

void SceneKaraage::KaraageMove(CVector3& pos)
{
	KTdiff = m_Tposition - pos;
	//からあげとトングの距離が近くて、
	//Bボタンが押されているとき。
	//アニメーション追加した時にその処理も追加
	//アニメーションが再生されている時という処理追加したら
	//閉じるときしかつかめないように出来るはず。
	if (KTdiff.Length() <= 8.0f &&
		Pad(0).IsPress(enButtonB)) {
		if (pushkara == false) {
			pushkara = true;
		}
		//m_player->Move()はプレイヤークラスに定義宣言
		//プレイヤーと同じ動きをする。
		//引数に好きな変数を入れたらどこでも使える。
		if (pushkara == true) {
			m_player->Move(pos);
		}
	}
}

void SceneKaraage::KaraageSyori()
{
	//完成したからあげがなければ
	if (kansei == false) {
		KaraageMove(m_Kposition);
		m_nama->SetPosition(m_Kposition);
		//からあげを一度持った後
		if (pushkara == true) {
			//シーンを変えたら、初期位置へ
			if (Pad(0).IsTrigger(enButtonRB1) ||
				Pad(0).IsTrigger(enButtonLB1)) {
				m_Kposition = m_StartPos;
				m_nama->SetPosition(m_Kposition);
				pushkara = false;
			}
			//からあげとトングが離れるか、Bを離した時
			if (KTdiff.Length() >= 20.0f ||
				!Pad(0).IsPress(enButtonB)) {
				KAdiff = m_aburaposition - m_Kposition;
				pushkara = false;
				//油との距離が近ければ揚げ始める。
				if (KAdiff.Length() <= 35.0f) {
					fry = true;
				}
				//遠ければ初期位置へ戻す。
				else {
					m_Kposition = m_StartPos;
					m_nama->SetPosition(m_Kposition);
					pushkara = false;
				}
			}

		}
	}
	//完成したからあげがあれば
	else {
		//OverS += GameTime().GetFrameDeltaTime();
		if (pushkara == false
			&& OverS >= 10) {
			m_Knseiposition = m_KnseiStartposition;
			m_kansei->SetPosition(m_Knseiposition);
			pushkara = false;
			kansei = false;
			OverS = 0;
		}
		//完成したからあげを動かすようにする。
		KaraageMove(m_Knseiposition);
		m_kansei->SetPosition(m_Knseiposition);
		KSdiff = m_Sposition - m_Knseiposition;
		//からあげを一度持った後、
		if (pushkara == true) {
			//シーンを変えたらそのまま消す
			if (Pad(0).IsTrigger(enButtonRB1) ||
				Pad(0).IsTrigger(enButtonLB1)) {
				m_Knseiposition = m_KnseiStartposition;
				m_kansei->SetPosition(m_Knseiposition);
				OverS = 0;
				pushkara = false;
				kansei = false;
			}
			//からあげとトングが離れるか、Bを離した時
			if (KTdiff.Length() >= 20.0f ||
				!Pad(0).IsPress(enButtonB)) {
				KSdiff = m_Sposition - m_Knseiposition;
				//お皿の上で離したら
				//完成個数を増やす。
				if (KSdiff.Length() <= 20.0f) {
					pushkara = false;
					m_Knseiposition = m_KnseiStartposition;
					m_kansei->SetPosition(m_Knseiposition);
					OverS = 0;
					KanseiKosuu++;
					kansei = false;
				}
				//遠ければ
				else {
					//完成個数は増やさずに消す。
					m_Knseiposition = m_KnseiStartposition;
					m_kansei->SetPosition(m_Knseiposition);
					OverS = 0;
					pushkara = false;
					kansei = false;
				}
			}

		}
	}
}

void SceneKaraage::FrySyori()
{
	KAdiff = m_aburaposition - m_Kposition;
	//油との距離が離れてしまったら。
	if (KAdiff.Length() >= 35.0f) {
		m_Kposition = m_StartPos;
		m_nama->SetPosition(m_Kposition);
		fry = false;
		pushkara = false;
		KaraageS = 0.0f;
	}
	if (KaraageS >= 10) {
		//完成したからあげを出す
		m_Knseiposition = m_Kposition;
		m_kansei->SetPosition(m_Knseiposition);
		kansei = true;

		m_Kposition = m_StartPos;
		m_nama->SetPosition(m_Kposition);
		fry = false;
		pushkara = false;
		KaraageS = 0.0f;
	}
}

void SceneKaraage::Update()
{
	//今のシーンがからあげの処理なら、動かす
		//カーソルをReturnMowSceneに持っていったらどの番号がどのシーンかわかります。
	nowscene = m_camera->ReturnNowScene();
	if (nowscene == 0) {
		m_player->RgripAnimation();
		TongMove();
		KaraageSyori();
	}
	if (Pad(0).IsTrigger(enButtonRB1) ||
		Pad(0).IsTrigger(enButtonLB1)) {
		m_player->RopenAnimation();
	}
	//変数はシーンがからあげでなくても動かす
	if (fry == true) {
		//これでKaraageSに秒数を足せる
		KaraageS += GameTime().GetFrameDeltaTime();
		FrySyori();
	}
	if (kansei == true) {
		OverS += GameTime().GetFrameDeltaTime();
	}
	//m_nama->SetEmissionColor({ 1.0f,1.0f,1.0f });
	/*CVector3 colar;
	colar.x = 0.0f;
	colar.y = 0.0f;
	colar.z = 0.0f;
	swprintf_s(text, L"%02d", KanseiKosuu);
	m_fontkansei->SetText(text);
	m_fontkansei->SetColor(colar);*/
}