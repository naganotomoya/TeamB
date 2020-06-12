#include "stdafx.h"
#include "KaraageGenerator.h"
#include "SceneKaraage.h"
#include "Player.h"
#include "Camera.h"

KaraageGenerator::KaraageGenerator()
{
}

KaraageGenerator::~KaraageGenerator()
{
	//DeleteGO(m_tong);
	DeleteGO(m_nama);
	//DeleteGO(m_abura);
	//DeleteGO(m_osara);
	DeleteGO(m_kansei);
	DeleteGO(baa);
	DeleteGO(waku);
	DeleteGO(m_age);

}

bool KaraageGenerator::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	m_karaage = FindGO<SceneKaraage>("karaage");
	//トング
	//m_tong = NewGO<prefab::CSkinModelRender>(0, "tong");
	//m_tong->Init(L"modelData/tongs.cmo");
	////モデル調整したら下のは多分いらない。
	//m_Trotation.SetRotationDeg(CVector3::AxisX, 180.0f);
	//m_tong->SetRotation(m_Trotation);
	//m_tong->SetScale({ 2.0f,2.0f,2.0f });
	////生のからあげ
	m_nama = NewGO<prefab::CSkinModelRender>(0);
	//m_nama->Init(L"modelData/KaraageS/Nama.cmo");
	m_nama->Init(L"modelData/KaraageS/kara/namakara.cmo");
	m_Kposition = { 74.0f,0.0f,-5.0f };
	m_StartPos = m_Kposition;
	m_nama->SetPosition(m_Kposition);
	//お皿
	/*m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_osara->SetRotation(m_Srotation);
	m_Sposition = { -60.0f,0.0f,-10.0f };
	m_osara->SetPosition(m_Sposition);*/

	//油
	//2D表示するときそのままだとでないと思うから3D表示にして反転させてください。
	//m_abura = NewGO<prefab::CSpriteRender>(0);
	//m_abura->Init(
	//	L"sprite/Phaikei/Abura.dds",
	//	MainCamera().GetWidth(),
	//	MainCamera().GetHeight(),
	//	true	//3D表示
	//);
	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//反転
	//m_abura->SetScale({ 0.04f,0.08f,0.05f });
	//m_aburaposition = { -8.5f,0.0f,-2.5f };
	//m_abura->SetPosition(m_aburaposition);
	//m_abura->SetRotation(Hanten);					//反転を適応
	//m_abura->SetMulColor({ 1.0f,1.0f,1.0f,0.8f });
	////完成したからあげ
	m_kansei = NewGO<prefab::CSkinModelRender>(0);
	//m_kansei->Init(L"modelData/KaraageS/Kansei.cmo");
	m_Knseiposition = m_KnseiStartposition;
	m_kansei->SetPosition(m_Knseiposition);

	//m_fontkansei = NewGO<prefab::CFontRender>(0);
	waku = NewGO<prefab::CSpriteRender>(0);
	baa = NewGO<prefab::CSpriteRender>(0);
	baa->SetPivot({ 0.0f,0.5f });
	/*baa->Init(L"sprite/Hiyoko/ba-.dds", 250.0f, 250.0f);
	baa->SetPivot(piv);
	baa->SetPosition({ -635.0f,230.0f,0.0f });*/

	m_age = NewGO<prefab::CSoundSource>(0);
	m_age->Init(L"sound/SE/age.wav");
	m_age->SetVolume(0.0f);

	return true;
}

//void KaraageGenerator::TongMove()
//{
//	//プレイヤーのポジションを使って
//	//トングのポジションにする
//	m_Tposition = m_player->ReturnRPlayerPosition();
//	m_Tposition.x += 2.0f;
//	m_Tposition.y += 25.0f;
//	m_Tposition.z += -3.0f;
//	m_tong->SetPosition(m_Tposition);
//}

void KaraageGenerator::KaraageMove(CVector3& pos, float dif)
{
	KTdiff = m_Tongposition - pos;
	//からあげとトングの距離が近くて、
	//Bボタンが押されているとき。
	//アニメーション追加した時にその処理も追加
	//アニメーションが再生されている時という処理追加したら
	//閉じるときしかつかめないように出来るはず。
	if (KTdiff.Length() <= dif &&
		Pad(0).IsPress(enButtonB)) {
		//m_player->Move()はプレイヤークラスに定義宣言
		//プレイヤーと同じ動きをする。
		//引数に好きな変数を入れたらどこでも使える。
		m_player->Move(pos);
	}
}

void KaraageGenerator::KaraageSyori()
{
	/*初期位置、待機*/
	if (m_state == StateIdle) {
		//生からと完成したからあげを初期ポジに戻す。
		m_Kposition = m_StartPos;
		//m_Knseiposition = m_KnseiStartposition;
		//からあげトングの距離
		KTdiff = m_Tongposition - m_Kposition;
		//からあげとトングが近くて、Bが押されていると、
		//Statepushに移動
		if (KTdiff.Length() <= 8.0f &&
			Pad(0).IsPress(enButtonB)) {
			m_state = Statepush;
		}
	}
	/*生から持った状態*/
	if (m_state == Statepush) {
		//生からあげを動かす。
		KaraageMove(m_Kposition, 8.0f);
		//シーンを変えたら、初期位置へ
		if (Pad(0).IsTrigger(enButtonRB1) ||
			Pad(0).IsTrigger(enButtonLB1)) {
			//m_state = StateIdle;
			m_karaage->minusNowkara();
			DeleteGO(this);
		}
		//Bを離した時、油と近ければ次の処理
		if (!Pad(0).IsPress(enButtonB) ||
			KTdiff.Length() >= 10.0f) {
			//からあげと油の距離
			KAdiff = m_aburaposition - m_Kposition;
			if (KAdiff.Length() <= 35.0f) {
				wakupos = m_Kposition;
				wakupos.z += 3.0f;
				baapos = m_Kposition;
				baapos.z += 3.0f;
				baapos.x += 5.0f;
				baa->Init(
					L"sprite/Karaage/baa.dds",
					MainCamera().GetWidth(),
					MainCamera().GetHeight(),
					true);
				baa->SetRotation(Hanten);
				baa->SetScale(SScale);
				baa->SetPosition(baapos);
				waku->Init(
					L"sprite/Karaage/baawaku.dds",
					MainCamera().GetWidth(),
					MainCamera().GetHeight(),
					true);
				waku->SetRotation(Hanten);
				waku->SetScale(SScale);
				waku->SetPosition(wakupos);
				m_karaage->minusNowkara();
				m_state = Statefry;
			}
			//遠ければ初期位置へ戻す。
			else {
				//m_state = StateIdle;
				m_karaage->minusNowkara();
				DeleteGO(this);
			}
		}
	}
	/*揚げる状態*/
	if (m_state == Statefry) {
		baaScale.x = KaraageS * 0.0008f;
		baa->SetScale(baaScale);

		m_age->Play(true);
		m_age->SetVolume(1.0f);

		//指定した秒数経ったら
		if (KaraageS >= 10.0f) {
			//完成したからあげを出す
			//m_kansei->Init(L"modelData/KaraageS/Kansei.cmo");
			m_kansei->Init(L"modelData/KaraageS/kara/Age.cmo");
			m_Knseiposition = m_Kposition;
			//m_Kposition = m_StartPos;
			m_nama->SetScale(ZeroScale);
			//今あるからあげの個数の変更
			//m_karaage->minusNowkara();
			//秒数を初期に戻して、Statekanseiに移動
			KaraageS = 0.0f;
			m_state = Statekansei;
		}
	}
	/*完成したからあげがある状態*/
	if (m_state == Statekansei) {

		if (KAdiff.Length() <= 35.0f) {
			m_age->SetVolume(0.5f);
		}
		else {
			m_age->SetVolume(0.0f);
		}

		baa->SetMulColor(baacolor);
		baaScale.x = (OverS / 2) * 0.0008f;
		baa->SetScale(baaScale);
		wakupos = m_Knseiposition;
		wakupos.z += 3.0f;
		baapos = m_Knseiposition;
		baapos.z += 3.0f;
		baapos.x += 5.0f;
		baa->SetPosition(baapos);
		waku->SetPosition(wakupos);
		//それぞれの距離
		KSdiff = m_Sposition - m_Knseiposition;
		KTdiff = m_Tongposition - m_Knseiposition;
		KAdiff = m_aburaposition - m_Knseiposition;
		//完成したからあげを動かす
		KaraageMove(m_Knseiposition, 8.0f);
		//持ってるじょうたいで他のシーン行ったら戻す。
		if (Pad(0).IsPress(enButtonB)) {
			if (Pad(0).IsTrigger(enButtonRB1) ||
				Pad(0).IsTrigger(enButtonLB1)) {
				//m_state = StateIdle;
				DeleteGO(this);
			}
		}
		//Bを離すか、トングとからあげが離れた時、
		if (!Pad(0).IsPress(enButtonB) ||
			KTdiff.Length() >= 10.0f) {
			//油と近ければ何もしない
			if (KAdiff.Length() <= 35.0f) {

			}
			else {
				//お皿と近ければ
				if (KSdiff.Length() <= 20.0f) {
					prefab::CSoundSource* pikon;
					pikon = NewGO<prefab::CSoundSource>(0);
					pikon->Init(L"sound/SE/pikon.wav");
					pikon->Play(false);

					//完成をプラス、オーバータイムを0にして
					//StateIdleに移動
					//KanseiKosuu++;
					m_karaage->PlusKaraageKansei();
					OverS = 0.0f;
					//m_state = StateIdle;
					DeleteGO(this);

				}//遠ければ初期位置に戻す。
				else {
					prefab::CSoundSource* bubu;
					bubu = NewGO<prefab::CSoundSource>(0);
					bubu->Init(L"sound/SE/cancel.wav");
					bubu->Play(false);

					OverS = 0.0f;
					//m_state = StateIdle;
					DeleteGO(this);
				}
			}
		}
		//オーバータイムが指定以上になったら
		//初期に戻す
		if (OverS <= 0.0f) {
			OverS = 20.0f;
			//m_state = StateIdle;
			DeleteGO(this);
		}
	}
}

void KaraageGenerator::Update()
{
	KaraageSyori();				//からあげの処理
	//今のシーンがからあげの処理なら、動かす
		//カーソルをReturnMowSceneに持っていったらどの番号がどのシーンかわかります。
	nowscene = m_camera->ReturnNowScene();
	if (nowscene == 0) {
		m_Tongposition = m_karaage->ReturnTongPos();
		//m_player->RgripAnimation();	//プレイヤーはずっと握っておく。
		//TongMove();					//トングの動き
		//KaraageSyori();				//からあげの処理
	}
	else {
		m_age->SetVolume(0.0f);
	}
	//LかR押したら右手を開く
	/*if (Pad(0).IsTrigger(enButtonRB1) ||
		Pad(0).IsTrigger(enButtonLB1)) {
		m_player->RopenAnimation();
	}*/
	//からあげを揚げる秒数のカウント
	if (m_state == Statefry) {
		KaraageS += GameTime().GetFrameDeltaTime();
	}
	//オーバータイムのカウント
	if (m_state == Statekansei /*&&
		!Pad(0).IsPress(enButtonB)*/) {
		OverS -= GameTime().GetFrameDeltaTime();
		//karaclo = (19-OverS) / 20.0f;
	}
	m_nama->SetPosition(m_Kposition);
	m_kansei->SetPosition(m_Knseiposition);

	//m_kansei->SetEmissionColor({ 0.0f, 0.0f, karaclo });
	//m_nama->SetEmissionColor({ 1.0f,1.0f,1.0f });
	/*CVector3 colar;
	colar.x = 0.0f;
	colar.y = 0.0f;
	colar.z = 0.0f;
	swprintf_s(text, L"%02d", KanseiKosuu);
	m_fontkansei->SetText(text);
	m_fontkansei->SetColor(colar);*/
}