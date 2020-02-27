#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	DeleteGO(m_Rhand);
}

bool Player::Start()
{
	//右手の表示、アニメーション
	m_Rhand = NewGO<prefab::CSkinModelRender>(0);
	m_Rac[rhandAC_open].Load(L"animData/Hand/Ropen.tka");
	m_Rac[rhandAC_grip].Load(L"animData/Hand/Rgrip.tka");
	m_Rac[rhandAC_open].SetLoopFlag(false);
	m_Rac[rhandAC_grip].SetLoopFlag(false);
	m_Rhand->Init(L"modelData/Hand/RHand.cmo", m_Rac, rhandAC_Num);
	//m_Rhand->SetScale({ 5.0f,5.0f,5.0f });
	//左手の表示、アニメーション
	/*m_Lhand = NewGO<prefab::CSkinModelRender>(0);
	m_Lac[lhandAC_open].Load(L"animData/Hand/Lopen2.tka");
	m_Lac[lhandAC_grip].Load(L"animData/Hand/Lgrip2.tka");
	m_Lac[lhandAC_open].SetLoopFlag(false);
	m_Lac[lhandAC_grip].SetLoopFlag(false);
	m_Lhand->Init(L"modelData/Hand/LHand2.cmo", m_Lac, lhandAC_Num);
	m_Lhand->SetPosition({ 20.0f,0.0f,0.0f });*/

	m_Lhand = NewGO<prefab::CSkinModelRender>(0);
	m_Lhand->Init(L"modelData/Hand/LHand.cmo");
	m_Lhand->SetPosition({ -20.0f,0.0f,0.0f });

	return true;
}

void Player::Update()
{
	if (Pad(0).IsPress(enButtonB)) {
		m_Rhand->PlayAnimation(rhandAC_grip);
	}
	else {
		m_Rhand->PlayAnimation(rhandAC_open);
	}
	//if (Pad(0).IsPress(enButtonA)) {
	//	m_Lhand->PlayAnimation(lhandAC_grip);
	//}
	//else {
	//	m_Lhand->PlayAnimation(lhandAC_open);
	//}
}