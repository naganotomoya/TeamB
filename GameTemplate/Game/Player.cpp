#include "stdafx.h"
#include "Player.h"
#include "Camera.h"

Player::Player()
{
}

Player::~Player()
{
	DeleteGO(m_Rhand);
	DeleteGO(m_Lhand);
}

bool Player::Start()
{
	m_camera = FindGO<Camera>("camera");
	scenenum = m_camera->Scenenum();
	//右手の表示、アニメーション
	m_Rhand = NewGO<prefab::CSkinModelRender>(0);
	m_Rac[rhandAC_open].Load(L"animData/Hand/Ropen.tka");
	m_Rac[rhandAC_grip].Load(L"animData/Hand/Rgrip.tka");
	m_Rac[rhandAC_open].SetLoopFlag(false);
	m_Rac[rhandAC_grip].SetLoopFlag(false);
	m_Rhand->Init(L"modelData/Hand/RHand.cmo", m_Rac, rhandAC_Num);
	m_Rhand->SetPosition(m_Rposition);
	//左手の表示、アニメーション
	m_Lhand = NewGO<prefab::CSkinModelRender>(0);
	m_Lac[lhandAC_open].Load(L"animData/Hand/Lopen.tka");
	m_Lac[lhandAC_grip].Load(L"animData/Hand/Lgrip.tka");
	m_Lac[lhandAC_open].SetLoopFlag(false);
	m_Lac[lhandAC_grip].SetLoopFlag(false);
	m_Lhand->Init(L"modelData/Hand/LHand.cmo", m_Lac, lhandAC_Num);
	m_Lhand->SetPosition(m_Lposition);

	return true;
}
void Player::SetXPosition(float x)
{
	m_Rposition.x += x * (scenenum - 1);
	m_Lposition.x += x * (scenenum - 1);
}

void Player::Animation()
{
	/*if (Pad(0).IsPress(enButtonB)) {
		m_Rhand->PlayAnimation(rhandAC_grip);
	}
	else {
		m_Rhand->PlayAnimation(rhandAC_open);
	}*/
	if (Pad(0).IsPress(enButtonB)) {
		m_Lhand->PlayAnimation(lhandAC_grip);
	}
	else {
		m_Lhand->PlayAnimation(lhandAC_open);
	}
}

void Player::Move()
{
	//カメラが移動するときの処理
	nowscene = m_camera->ReturnNowScene();
	if (Pad(0).IsTrigger(enButtonRB1)) {
		if (nowscene != (scenenum - 1)) {
			PlusXPosition(-CX);
		}
		else {
			SetXPosition(CX);
		}
	}
	if (Pad(0).IsTrigger(enButtonLB1)) {
		if (nowscene != 0) {
			PlusXPosition(CX);
		}
		else {
			SetXPosition(-CX);
		}
	}
	//左右
	m_Lposition.x -= Pad(0).GetLStickXF() * movespeed;
	m_Lposition.y += Pad(0).GetLStickYF() * movespeed;
}

void Player::Update()
{
	Animation();
	Move();
	m_Rhand->SetPosition(m_Rposition);
	m_Lhand->SetPosition(m_Lposition);
}