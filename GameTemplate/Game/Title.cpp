#include "stdafx.h"
#include "Title.h"
#include "Game.h"


Title::Title()
{
}

Title::~Title()
{
	//DeleteGO(m_spriteRender);

	DeleteGO(m_fontAgekire);
	DeleteGO(m_fontKaraage);
	DeleteGO(m_Press);
	DeleteGO(m_age);

}
bool Title::Start()
{
	/*m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"sprite/sneak-kill.dds", 1280.0f, 720.0f);*/

	m_fontAgekire = NewGO<prefab::CFontRender>(0);
	m_fontAgekire->SetText(L"あげきれ");
	m_fontAgekire->SetScale(5.0f);
	m_fontAgekire->SetColor(AKcolor);

	m_fontKaraage = NewGO<prefab::CFontRender>(0);
	m_fontKaraage->SetText(L"からあげ!");
	m_fontKaraage->SetPosition(KaraagePos);
	m_fontKaraage->SetScale(0.0f);
	m_fontKaraage->SetColor(AKcolor);
	//m_fontKaraage->SetPivot({ 0.5f,0.5f });

	m_Press = NewGO<prefab::CFontRender>(0);
	m_Press->SetText(L"Press A Button");
	m_Press->SetScale(0.0f);
	m_Press->SetPivot({ 0.5f,0.5f });
	m_Press->SetPosition({ 0.0f,-250.0f });

	m_age = NewGO<prefab::CSoundSource>(0);
	m_age->Init(L"sound/SE/age.wav");
	m_age->SetVolume(vol);
	m_age->Play(true);
	//MovePos = { 2.0,-1.0f };

	return true;
}
void Title::volup()
{
	if (vol <= 1.0f) {
		vol += 0.005f;
	}
	m_age->SetVolume(vol);
}
void Title::TaxtMove()
{
	/*あげきれの処理*/
		//Downステート
	if (m_Astate == Down) {
		MoveY += 0.02;
		AgekirePos.x += 2.0f;
		AgekirePos.y -= MoveY;
		//yが10０以下でステートを移行
		if (AgekirePos.y <= 100.0f) {
			Bundnum++;
			//３回目のバウンドならストップ
			//からあげ！の方の処理に進む
			if (Bundnum == 3) {
				prefab::CSoundSource* syakin;
				syakin = NewGO<prefab::CSoundSource>(0);
				syakin->Init(L"sound/SE/syakin.wav");
				syakin->Play(false);

				m_Astate = Stop;
				m_Kstate = Big;
			}
			//それ以下ならUp
			else {
				prefab::CSoundSource* puyo;
				puyo = NewGO<prefab::CSoundSource>(0);
				puyo->Init(L"sound/SE/puyon.wav");
				puyo->Play(false);

				m_Astate = Up;
			}
		}
	}
	//Upステート
	if (m_Astate == Up) {

		//MoveY += 0.02;
		AgekirePos.x += 2.0f;
		AgekirePos.y += MoveY;
		if (Bundnum == 1) {
			if (AgekirePos.y >= 200.0f) {
				m_Astate = Down;
			}
		}
		if (Bundnum == 2) {
			if (AgekirePos.y >= 90.0f) {
				m_Astate = Down;
			}
		}
	}
	//Stopステート
	if (m_Astate == Stop) {
		MoveY = 0.0f;
	}

	m_fontAgekire->SetPosition(AgekirePos);

	/*からあげ！の処理*/
	if (m_Kstate == Idle) {

	}
	//大きくする
	if (m_Kstate == Big) {
		Kscal += 0.2f;
		if (Kscal >= 10.0f) {
			m_Kstate = Small;
		}
	}
	//小さくする
	if (m_Kstate == Small) {
		Kscal -= 0.5f;
		if (Kscal <= 5.0f) {
			m_Kstate = KStop;
			m_Pstate = in;
			m_Press->SetScale(3.0f);
		}
	}
	if (m_Kstate == KStop) {
		Kscal = 5.0f;
	}
	m_fontKaraage->SetScale(Kscal);

	/*PressAの処理*/
	if (m_Pstate == PIdle) {

	}
	if (m_Pstate == in) {
		color.w += 0.01;
		if (color.w >= 1.0f) {
			m_Pstate = out;
		}
	}
	if (m_Pstate == out) {
		color.w -= 0.01f;
		if (color.w <= 0.0f) {
			m_Pstate = in;
		}
	}
	m_Press->SetColor(color);

}
void Title::Update()
{
	TaxtMove();
	if (m_Pstate != Idle) {
		volup();
	}
	if (Pad(0).IsPress(enButtonA) == true) {
		//もしもaボタンを押されたら。
		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}
}