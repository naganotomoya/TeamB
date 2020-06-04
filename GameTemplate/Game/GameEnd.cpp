#include "stdafx.h"
#include "Title.h"
#include "GameEnd.h"
GameEnd::GameEnd()
{
}

GameEnd::~GameEnd()
{
	DeleteGO(m_fontkekka);
	DeleteGO(m_fontteikyou);
	DeleteGO(m_fontkazu);
	DeleteGO(m_fontPress);
	DeleteGO(m_hiyoko);
}
bool GameEnd::Start()
{
	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);
	//けっかはっぴょー！
	m_fontkekka = NewGO<prefab::CFontRender>(0);
	m_fontkekka->SetPivot(CenterPivot);
	m_fontkekka->SetText(L"Result");
	m_fontkekka->SetPosition(kekkapos);
	m_fontkekka->SetColor({ 1.0f,0.0f,0.0f });
	m_fontkekka->SetScale(5.0f);
	//カラッ
	m_fontteikyou = NewGO<prefab::CFontRender>(0);
	m_fontteikyou->SetText(L"カラッ");
	m_fontteikyou->SetPivot(CenterPivot);
	m_fontteikyou->SetPosition(teikyoupos);
	m_fontteikyou->SetColor({ 1.0f,0.0f,0.0f });
	m_fontteikyou->SetScale(2.0f);
	//完成品の数
	m_fontkazu = NewGO<prefab::CFontRender>(0);
	m_fontkazu->SetPivot(CenterPivot);
	m_fontkazu->SetScale(5.0f);
	m_fontkazu->SetPosition(kazupos);
	m_fontkazu->SetColor({ 0.0f,0.0f,0.0f });
	//PressAnyKey
	m_fontPress = NewGO<prefab::CFontRender>(0);
	m_fontPress->SetPosition(presspos);
	m_fontPress->SetScale(2.0f);

	//画像
	m_hiyoko = NewGO<prefab::CSpriteRender>(0);
	m_hiyoko->Init(
		L"sprite/Hiyoko/Fhiyoko.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true
	);
	m_hiyoko->SetPivot({ CenterPivot });
	m_hiyoko->SetPosition(hiyokoPos);
	m_hiyoko->SetRotation(Hanten);
	m_hiyoko->SetScale(hiyokoScale);


	return true;
}
void GameEnd::fontFade()
{
	//fade = 1.0f;
	if (Sfade == true) {
		colorfont.w += 0.01;
		if (colorfont.w >= 1.0f) {
			Sfade = false;
		}
	}
	if (Sfade == false) {
		colorfont.w -= 0.01f;
		if (colorfont.w <= 0.0f) {
			Sfade = true;
		}
	}
	m_fontPress->SetColor(colorfont);
}

void GameEnd::SprintCH()
{
	//待機状態
	if (m_state == Idle) {
		if (timer >= 2.0f) {
			m_state = Big;
		}
	}
	//一回目の拡大
	if (m_state == Big) {
		//画像の拡大率を変える
		m_hiyoko->SetScale({ 0.1f,0.1f,0.1f });
		if (timer >= 4.0f) {
			m_state = Big2;
		}
	}
	//二回目の拡大
	if (m_state == Big2) {
		//画像の拡大率を変える
		m_hiyoko->SetScale({ 0.15f,0.15f,0.15f });
		if (timer >= 8.0f) {
			m_hiyoko->SetScale(hiyokoScale);
			//完成個数によって画像を変える
				//成功
			if (kazu >= 15) {
				m_state = Sugoi;
			}
			//普通
			else if (kazu >= 10) {
				m_state = Futuu;
			}
			//残念
			else {
				m_state = Kantan;
			}
		}

	}
	//それぞれの結果による分岐
	if (m_state == Sugoi) {
		//画像の表示
		m_hiyoko->Init(
			L"sprite/Hiyoko/Chiyoko.dds",
			MainCamera().GetWidth(),
			MainCamera().GetHeight(),
			true
		);
	}
	if (m_state == Futuu) {
		//画像の表示
		m_hiyoko->Init(
			L"sprite/Hiyoko/Fhiyoko.dds",
			MainCamera().GetWidth(),
			MainCamera().GetHeight(),
			true
		);
	}
	if (m_state == Kantan) {
		//画像の表示
		m_hiyoko->Init(
			L"sprite/Hiyoko/Whiyoko.dds",
			MainCamera().GetWidth(),
			MainCamera().GetHeight(),
			true
		);
	}
}

void GameEnd::Update()
{
	SprintCH();
	timer += GameTime().GetFrameDeltaTime();
	//秒数過ぎるまではランダムに数字を表示する。
	if (timer <= 8.0f) {
		randamu = rand() % 99;
		swprintf_s(text, L"%02d", randamu);
		m_fontkazu->SetText(text);
	}
	//300過ぎたら結果を表示
	else {
		swprintf_s(text, L"%02d", kazu);
		m_fontkazu->SetText(text);
		//PressAnyKeyと表示
		m_fontPress->SetText(L"PressAnyKey");
		fontFade();
		//何かボタンを押したらタイトルに戻る。
		if (Pad(0).IsPressAnyKey() == true) {
			NewGO<Title>(0, nullptr);
			DeleteGO(this);
		}
	}

}