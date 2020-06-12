#include "stdafx.h"
#include "HaikeiMove.h"

HaikeiMove::HaikeiMove()
{
}

HaikeiMove::~HaikeiMove()
{
	DeleteGO(m_haikei);

}
bool HaikeiMove::Start()
{
	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//”½“]
	m_haikei = NewGO<prefab::CSpriteRender>(0);
	m_haikei->Init(
		L"sprite/Hiyoko/hiyokohaikei.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true	//3D•\Ž¦
	);
	m_haikei->SetScale({ 0.3f,0.3f,0.0f });
	HKpos = { -80.0f,0.0f,-0.5f };
	m_haikei->SetPosition(HKpos);
	m_haikei->SetRotation(Hanten);					//”½“]‚ð“K‰ž

	return true;
}
void HaikeiMove::Update()
{
	if (yoko == false) {
		HKpos.x += 0.1f;
		if (HKpos.x >= 80.0f) {
			yoko = true;
		}
	}
	if (yoko == true) {
		HKpos.x -= 0.1f;
		if (HKpos.x <= -80.0f) {
			yoko = false;
		}
	}
	m_haikei->SetPosition(HKpos);

}