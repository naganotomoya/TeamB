#include "stdafx.h"
#include "Game.h"
#include "Title.h"
//#include "ProgressBar.h"
#include "Player.h"
#include "Camera.h"
#include "SceneKaraage.h"
#include "ScenePoteto.h"
#include "SceneDrink.h"
#include "SceneMorituke.h"
#include "SceneAraimono.h"
#include "SceneKaikei.h"
#include "GameEnd.h"
#include "tkEngine/light/tkDirectionLight.h"

Game::Game()
{
}


Game::~Game()
{

	//
	//DeleteGO(m_skinModelRender);
	DeleteGO(m_spriteRender);
	//DeleteGO(Progressbar);
	DeleteGO(m_player);
	DeleteGO(m_camera);
	DeleteGO(m_karaage);
	DeleteGO(m_poteto);
	DeleteGO(m_drink);
	DeleteGO(m_morituke);
	DeleteGO(m_araimono);
	DeleteGO(m_kaikei);

	DeleteGO(m_fonttimer);
	DeleteGO(m_fontkosuu);
	DeleteGO(m_fontkanseihin);
}
bool Game::Start()
{
	////カメラを設定。
	//MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	//MainCamera().SetNear(10.0f);
	//MainCamera().SetFar(10000.0f);
	//MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	//MainCamera().Update();
	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");*/
	//m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	//m_spriteRender->Init(L"sprite/phaikei.dds", 1280.0f, 720.0f);

	//Progressbar = NewGO<ProgressBar>(0);
	m_player = NewGO<Player>(0, "player");
	m_camera = NewGO<Camera>(0, "camera");
	m_karaage = NewGO<SceneKaraage>(0, "karaage");
	m_poteto = NewGO<ScenePoteto>(0, "poteto");
	m_drink = NewGO<SceneDrink>(0, "drink");
	m_morituke = NewGO<SceneMorituke>(0, "morituke");
	m_araimono = NewGO<SceneAraimono>(0, "araimono");
	m_kaikei = NewGO<SceneKaikei>(0, "kaikei");

	m_fonttimer = NewGO<prefab::CFontRender>(0);
	m_fonttimer->SetPosition(timerPos);
	m_fonttimer->SetScale(2.0f);

	m_fontkanseihin = NewGO<prefab::CFontRender>(0);
	m_fontkanseihin->SetText(L"完成品：");
	m_fontkanseihin->SetPosition(kanseiPos);
	//m_fontkanseihin->SetColor({ 1.0f,0.0f,0.0f });
	//m_fontkanseihin->SetScale(2.0f);
	m_fontkosuu = NewGO<prefab::CFontRender>(0);
	m_fontkosuu->SetPosition(kosuuPos);

	return true;
}

void Game::KanseiCount()
{
	Kansei = m_karaage->ReturnKaraageKansei();
}

void Game::Update()
{
	KanseiCount();
	if (Pad(0).IsPress(enButtonStart) == true) {
		NewGO<Title>(0);
		DeleteGO(this);
	}


	//タイマー
	if (timer >= 0.0f) {
		timer -= GameTime().GetFrameDeltaTime();
	}
	else {
		NewGO<GameEnd>(0, "Gameend");
		DeleteGO(this);
	}
	int minute = (int)timer / 60;
	float sec = (int)timer % 60;
	swprintf_s(texttimer, L"%02d:%02.0f", minute, sec);
	m_fonttimer->SetText(texttimer);

	swprintf_s(textkosuu, L"%02d", Kansei);
	m_fontkosuu->SetText(textkosuu);

}