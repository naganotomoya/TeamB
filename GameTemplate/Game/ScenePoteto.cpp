#include "stdafx.h"
#include "ScenePoteto.h"
ScenePoteto::ScenePoteto()
{
}
ScenePoteto::~ScenePoteto()
{
}

bool ScenePoteto::Start()
{
	//ポテト
	m_Poteto = NewGO<prefab::CSkinModelRender>(0, "Poteto");
	m_Poteto->Init(L"modelData/poteto.cmo");
	m_Pposition = { 70.0f,0.0f,0.0f};
	m_Poteto->SetPosition(m_Pposition);
	//お皿
	m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");

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
	return true;
}

void ScenePoteto::Update()
{
}