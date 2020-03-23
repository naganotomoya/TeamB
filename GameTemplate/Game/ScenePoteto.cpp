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
	//�|�e�g
	m_Poteto = NewGO<prefab::CSkinModelRender>(0, "Poteto");
	m_Poteto->Init(L"modelData/poteto.cmo");
	m_Pposition = { 70.0f,0.0f,0.0f};
	m_Poteto->SetPosition(m_Pposition);
	//���M
	m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");

	//��
	//2D�\������Ƃ����̂܂܂��ƂłȂ��Ǝv������3D�\���ɂ��Ĕ��]�����Ă��������B
	m_abura = NewGO<prefab::CSpriteRender>(0);
	m_abura->Init(
		L"sprite/Phaikei/Abura.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true	//3D�\��
	);
	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//���]
	m_abura->SetScale({ 0.05f,0.1f,0.05f });
	m_aburaposition = { -10.0f,0.0f,-20.0f };
	m_abura->SetPosition(m_aburaposition);
	m_abura->SetRotation(Hanten);					//���]��K��
	return true;
}

void ScenePoteto::Update()
{
}