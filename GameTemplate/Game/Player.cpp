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
	m_Lhand = NewGO<prefab::CSkinModelRender>(0);
	m_Lac[lhandAC_open].Load(L"animData/Hand/Ropen.tka");
	m_Lac[lhandAC_grip].Load(L"animData/Hand/Rgrip.tka");
	m_Lac[lhandAC_osara].Load(L"animData/Hand/LOsara.tka");
	m_Lac[lhandAC_osaragrip].Load(L"animData/Hand/LOsaragri.tka");
	m_Lac[lhandAC_open].SetLoopFlag(false);
	m_Lac[lhandAC_grip].SetLoopFlag(false);
	m_Lac[lhandAC_osara].SetLoopFlag(false);
	m_Lac[lhandAC_osaragrip].SetLoopFlag(false);
	m_Lhand->Init(L"modelData/Hand/RHand.cmo", m_Lac, lhandAC_Num);
	m_Lhand->SetPosition(m_Lposition);
	//左手の表示、アニメーション
	m_Rhand = NewGO<prefab::CSkinModelRender>(0);
	m_Rac[lhandAC_open].Load(L"animData/Hand/Lopen.tka");
	m_Rac[lhandAC_grip].Load(L"animData/Hand/Lgrip.tka");
	m_Rac[lhandAC_open].SetLoopFlag(false);
	m_Rac[lhandAC_grip].SetLoopFlag(false);
	m_Rhand->Init(L"modelData/Hand/LHand.cmo", m_Rac, rhandAC_Num);
	m_Rhand->SetPosition(m_Rposition);
	return true;
}
void Player::SetXPosition(float x)
{
	m_Rposition.x += x * (scenenum - 1);
	m_Lposition.x += x * (scenenum - 1);
}


void Player::Animation()
{
	/*if (Pad(0).IsPress(enButtonA)) {
		m_Rhand->PlayAnimation(rhandAC_grip);
	}
	else {
		m_Rhand->PlayAnimation(rhandAC_open);
	}*/
	if (Pad(0).IsPress(enButtonB)) {
		m_Rhand->PlayAnimation(rhandAC_grip);
	}
	else {
		m_Rhand->PlayAnimation(rhandAC_open);
	}
}

void Player::Move(CVector3& pos)
{
	//左右
	pos.x -= Pad(0).GetLStickXF() * movespeed;
	pos.y += Pad(0).GetLStickYF() * movespeed;
	//移動制限
	if (pos.x >= tyuusin + 100) {
		(pos.x = tyuusin + 100);
	}
	if (pos.x <= tyuusin - 100) {
		(pos.x = tyuusin - 100);
	}
	if (pos.y >= 60.0f) {
		pos.y = 60.0f;
	}
	if (pos.y <= -60.0f) {
		pos.y = -60.0f;
	}
}

void Player::Update()
{
	//カメラが移動するときの処理
	nowscene = m_camera->ReturnNowScene();
	if (Pad(0).IsTrigger(enButtonRB1) &&
		(Pad(0).IsTrigger(enButtonLB1))) {
	}
	else {
		if (Pad(0).IsTrigger(enButtonRB1)) {
			if (nowscene != (scenenum - 1)) {
				PlusXPosition(-CX);
				tyuusin += -CX;
			}
			else {
				SetXPosition(CX);
				tyuusin += CX * (scenenum - 1);
			}
		}
		if (Pad(0).IsTrigger(enButtonLB1)) {
			if (nowscene != 0) {
				PlusXPosition(CX);
				tyuusin += CX;
			}
			else {
				SetXPosition(-CX);
				tyuusin += -CX * (scenenum - 1);
			}
		}
	}
	//Animation();
	Move(m_Rposition);
	m_Rhand->SetPosition(m_Rposition);
	m_Lhand->SetPosition(m_Lposition);
}