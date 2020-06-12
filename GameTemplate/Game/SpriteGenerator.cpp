#include "stdafx.h"
#include "SpriteGenerator.h"
#include "SceneKaikei.h"
#include "SceneKaraage.h"
#include "ScenePoteto.h"
#include "SceneMorituke.h"
#include "SceneDrink.h"
#include "SceneAraimono.h"

SpriteGenerator::SpriteGenerator()
{

}

SpriteGenerator::~SpriteGenerator()
{
	DeleteGO(baa);
	DeleteGO(m_sprite);
	//DeleteGO(waku);
	DeleteGO(CheckK);
	DeleteGO(CheckP);
	DeleteGO(CheckY);
	DeleteGO(CheckD);
}

bool SpriteGenerator::Start()
{

	m_karaage = FindGO<SceneKaraage>("karaage");
	m_poteto = FindGO<ScenePoteto>("poteto");
	m_morituke = FindGO<SceneMorituke>("morituke");
	m_drink = FindGO<SceneDrink>("drink");
	m_araimono = FindGO<SceneAraimono>("araimono");

	m_kaikei = FindGO<SceneKaikei>("kaikei");

	baa = NewGO<prefab::CSpriteRender>(0);
	baa->Init(L"sprite/Hiyoko/ba-.dds", 250.0f, 250.0f);
	baa->SetPivot(piv);
	baa->SetPosition({ -635.0f,230.0f,0.0f });

	m_sprite = NewGO<prefab::CSpriteRender>(0);
	m_sprite->SetPosition({ -510.0f,230.0f,0.0f });

	//waku = NewGO<prefab::CSpriteRender>(0);

	CheckK = NewGO<prefab::CSpriteRender>(0);
	CheckK->SetPosition(StartPos);
	CheckP = NewGO<prefab::CSpriteRender>(0);
	CheckP->SetPosition(StartPos);
	CheckY = NewGO<prefab::CSpriteRender>(0);
	CheckY->SetPosition(StartPos);
	CheckD = NewGO<prefab::CSpriteRender>(0);
	CheckD->SetPosition(StartPos);


	setscene = m_kaikei->KyakuNum();

	return true;
}
//それぞれのチェックマークの種類を決めて、個数を減らす。
void SpriteGenerator::CHKara()
{
	if (SetKara == false) {
		if (Kara >= 1) {
			CheckK->Init(L"sprite/Hiyoko/karaCH.dds", 250.0f, 250.0f);
			m_karaage->MinusKaraageKansei();
			SetKara = true;
		}
	}
}
void SpriteGenerator::CHPote()
{
	if (SetPote == false) {
		if (Pote >= 1) {
			CheckP->Init(L"sprite/Hiyoko/PoteCH.dds", 250.0f, 250.0f);
			m_poteto->SetPotetoKosuu();
			SetPote = true;
		}
	}
}
void SpriteGenerator::CHYasai()
{
	if (SetYasai == false) {
		if (Yasai >= 1) {
			CheckY->Init(L"sprite/Hiyoko/YasaiCH.dds", 250.0f, 250.0f);
			m_morituke->MinusKyabetuKansei();
			SetYasai = true;
		}
	}
}
void SpriteGenerator::CHDrink(int num)
{
	if (SetDrink == false) {
		//水の変更
		if (num == 1) {
			if (mizu >= 1) {
				CheckD->Init(L"sprite/Hiyoko/DrinkCH.dds", 250.0f, 250.0f);
				mizu--;
				SetDrink = true;
			}
		}
		//コーラの変更
		else if (num == 2) {
			if (kora >= 1) {
				CheckD->Init(L"sprite/Hiyoko/DrinkCH.dds", 250.0f, 250.0f);
				kora--;
				SetDrink = true;
			}
		}
		//お茶の変更
		else if (num == 3) {
			if (otya >= 1) {
				CheckD->Init(L"sprite/Hiyoko/DrinkCH.dds", 250.0f, 250.0f);
				otya--;
				SetDrink = true;
			}
		}
	}
}

void SpriteGenerator::SetPosX()
{
	if (setscene == scene) {
		m_sprite->SetPosition(StartPos);
		m_sprite->SetScale({ 1.0f,1.0f,1.0f });
		baa->SetPosition({ -635.0f,230.0f,0.0f });
		baa->SetScale({ 1.0f,1.0f,1.0f });
	}
	else {
		m_sprite->SetPosition({ -300.0f,230.0f,0.0f });
		m_sprite->SetScale(nextScale);
		baa->SetPosition({ -362.0f,230.0f,0.0f });
		baa->SetScale(nextScale);
	}
}
void SpriteGenerator::SpriteState()
{
	//ステートを変化させる
	if (m_state == Idle) {
		setstate = m_kaikei->RandamuKyaku();
		if (setstate == 0) {
			m_state = Girl;
		}
		if (setstate == 1) {
			m_state = Boy;
		}
		if (setstate == 2) {
			m_state = Oldman;
		}
		if (setstate == 3) {
			m_state = Fat;
		}
	}
	//それぞれのステートの処理
		//女の子のステート
	if (m_state == Girl) {
		m_sprite->Init(L"sprite/Hiyoko/girl.dds", 250.0f, 250.0f);
		m_kaikei->SetKyakuNum();
		m_state = GKaikei;
	}
	//男の子のステート
	if (m_state == Boy) {
		m_sprite->Init(L"sprite/Hiyoko/boy.dds", 250.0f, 250.0f);
		m_kaikei->SetKyakuNum();
		m_state = BKaikei;
	}
	//おじいさんのステート
	if (m_state == Oldman) {
		m_sprite->Init(L"sprite/Hiyoko/old.dds", 250.0f, 250.0f);
		m_kaikei->SetKyakuNum();
		m_state = OKaikei;
	}
	//太った人のステート
	if (m_state == Fat) {
		m_sprite->Init(L"sprite/Hiyoko/fat.dds", 250.0f, 250.0f);
		m_kaikei->SetKyakuNum();
		m_state = FKaikei;
	}

	//次のお客さんに進むステート
	if (m_state == NextKaikei) {
		ColorFade();
		if (fadeCount >= 3) {
			m_kaikei->Setninzuu();
			m_kaikei->NextTyuumon();
			m_state = DeleteThis;
		}
	}
	if (m_state == DeleteThis) {
		DeleteGO(this);
	}
}
void SpriteGenerator::KaikeiSyori()
{
	//会計のステート
//女の子
	if (m_state == GKaikei) {
		//ポテト、水、野菜
		CHPote();
		CHYasai();
		CHDrink(1);
		if (SetPote == true &&
			SetDrink == true &&
			SetYasai == true) {

			prefab::CSoundSource* piyo;
			piyo = NewGO<prefab::CSoundSource>(0);
			piyo->Init(L"sound/SE/hiyoko.wav");
			piyo->Play(false);

			m_kaikei->KanseiKo();
			m_state = NextKaikei;
		}
	}
	//男の子
	if (m_state == BKaikei) {
		//からあげ、ポテト、野菜
		CHKara();
		CHPote();
		CHYasai();
		if (SetKara == true &&
			SetPote == true &&
			SetYasai == true) {

			prefab::CSoundSource* piyo;
			piyo = NewGO<prefab::CSoundSource>(0);
			piyo->Init(L"sound/SE/hiyoko.wav");
			piyo->Play(false);

			m_kaikei->KanseiKo();
			m_state = NextKaikei;
		}
	}
	//おじいさん
	if (m_state == OKaikei) {
		//からあげ、お茶、野菜
		CHKara();
		CHDrink(3);
		CHYasai();
		if (SetKara == true &&
			SetDrink == true &&
			SetYasai == true) {

			prefab::CSoundSource* piyo;
			piyo = NewGO<prefab::CSoundSource>(0);
			piyo->Init(L"sound/SE/hiyoko.wav");
			piyo->Play(false);

			m_kaikei->KanseiKo();
			m_state = NextKaikei;
		}
	}
	//太った人
	if (m_state == FKaikei) {
		//からあげ、ポテト、コーラ
		CHKara();
		CHPote();
		CHDrink(2);
		if (SetKara == true &&
			SetPote == true &&
			SetDrink == true) {

			prefab::CSoundSource* piyo;
			piyo = NewGO<prefab::CSoundSource>(0);
			piyo->Init(L"sound/SE/hiyoko.wav");
			piyo->Play(false);

			m_kaikei->KanseiKo();
			m_state = NextKaikei;
		}
	}
}
void SpriteGenerator::NokoriBaa()
{
	timer -= GameTime().GetFrameDeltaTime();
	//タイマーの秒数で一個の会計済ませるようにする
	BaaScale.x = timer / 40.0f;
	baa->SetScale(BaaScale);
	if (timer <= 0.0f) {
		if (oto == false) {
			prefab::CSoundSource* pien;
			pien = NewGO<prefab::CSoundSource>(0);
			pien->Init(L"sound/SE/zannnenn.wav");
			pien->Play(false);
			oto = true;
		}
		m_state = NextKaikei;
	}
}
void SpriteGenerator::ColorFade()
{
	if (fade == false &&
		Fade.w >= 1.0f) {
		fade = true;
		fadeCount++;
	}
	if (fade == true &&
		Fade.w <= 0.0f) {
		fade = false;
	}

	if (fade == false) {
		Fade.w += 0.05f;
	}
	if (fade == true) {
		Fade.w -= 0.05f;
	}
	m_sprite->SetMulColor(Fade);
}
void SpriteGenerator::SetKosuu()
{
	Kara = m_karaage->ReturnKaraageKansei();
	Pote = m_poteto->ReturnKanseiPoteto();
	Yasai = m_morituke->ReturnKyabetuKansei();
	mizu = num;
	kora = num;
	otya = num;
}

void SpriteGenerator::Update()
{
	scene = m_kaikei->NowTyuumon();
	SpriteState();
	SetPosX();
	SetKosuu();
	//自分が処理中のお客の場合、
	if (setscene == scene) {
		KaikeiSyori();
		NokoriBaa();
	}
}