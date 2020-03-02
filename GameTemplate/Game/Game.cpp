#include "stdafx.h"
#include "Game.h"
#include "Title.h"
#include "ProgressBar.h"
#include "Player.h"
#include "Camera.h"
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
	m_player = NewGO<Player>(0,"player");
	m_camera = NewGO<Camera>(0,"camera");

	return true;
}

void Game::Update()
{
	if (Pad(0).IsPress(enButtonStart) == true) {
		NewGO<Title>(0);
		DeleteGO(this);
	}
}