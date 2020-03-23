#include "stdafx.h"
#include "SceneDrink.h"

SceneDrink::SceneDrink()
{
}
SceneDrink::~SceneDrink()
{
}
bool SceneDrink::Start()
{
	//ƒ‚ƒfƒ‹‚ğƒ[ƒh
	m_skinModelRenderer = NewGO<prefab::CSkinModelRender>(0,"koop1");
	m_skinModelRenderer->Init(L"modelData/koop1.cmo");
	m_skinModelRenderer->SetPosition({ -2550.0f,0.0f,0.0f });

	player = FindGO<Player>("player");
	return true;
}
void SceneDrink::Update()
{
	
	CVector3 diff = player->ReturnRPlayerPosition() - m_position;

}