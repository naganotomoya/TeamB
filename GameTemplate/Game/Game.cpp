#include "stdafx.h"
#include "Game.h"
#include "Title.h"
#include "ProgressBar.h"
#include "Player.h"
#include "Camera.h"
#include "SceneKaraage.h"
#include "ScenePoteto.h"
#include "SceneDrink.h"
#include "SceneMorituke.h"
#include "SceneAraimono.h"
#include "SceneKaikei.h"
#include "tkEngine/light/tkDirectionLight.h"

Game::Game()
{
}


Game::~Game()
{

	//DeleteGO(m_skinModelRender);
	DeleteGO(m_spriteRender);
	DeleteGO(Progressbar);
	DeleteGO(m_player);
	DeleteGO(m_camera);
	DeleteGO(m_karaage);
	DeleteGO(m_poteto);
	DeleteGO(m_drink);
	DeleteGO(m_morituke);
	DeleteGO(m_araimono);
	DeleteGO(m_kaikei);
}
bool Game::Start()
{
	////ÉJÉÅÉâÇê›íËÅB
	//MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	//MainCamera().SetNear(10.0f);
	//MainCamera().SetFar(10000.0f);
	//MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	//MainCamera().Update();
	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");*/
	//m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	//m_spriteRender->Init(L"sprite/phaikei.dds", 1280.0f, 720.0f);

	Progressbar = NewGO<ProgressBar>(0);
	m_player = NewGO<Player>(0, "player");
	m_camera = NewGO<Camera>(0, "camera");
	m_karaage = NewGO<SceneKaraage>(0, "karaage");
	m_poteto = NewGO<ScenePoteto>(0, "poteto");
	m_drink = NewGO<SceneDrink>(0, "drink");
	m_morituke = NewGO<SceneMorituke>(0, "morituke");
	m_araimono = NewGO<SceneAraimono>(0, "araimono");
	m_kaikei = NewGO<SceneKaikei>(0, "kaikei");

	return true;
}

void Game::Update()
{
	if (Pad(0).IsPress(enButtonStart) == true) {
		NewGO<Title>(0);
		DeleteGO(this);
	}
}