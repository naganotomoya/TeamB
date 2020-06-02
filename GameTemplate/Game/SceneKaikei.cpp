#include "stdafx.h"
#include "SceneKaikei.h"
SceneKaikei::SceneKaikei()
{
}
SceneKaikei::~SceneKaikei()
{

}

bool SceneKaikei::Start()
{
	//ƒ‚ƒfƒ‹‚ğƒ[ƒh
	m_hito = NewGO<prefab::CSkinModelRender>(0, "hito1");
	m_hito->Init(L"modelData/hito1.cmo");
	m_hito->SetPosition(m_position);
	

	return true;
}
void SceneKaikei::Update()
{

}