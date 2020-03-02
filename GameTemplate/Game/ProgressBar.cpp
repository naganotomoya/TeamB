#include "stdafx.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar()
{
}

ProgressBar::~ProgressBar()
{
	DeleteGO(k_spriteRender);
	DeleteGO(p_spriteRender);
}

bool ProgressBar::Start()
{
	CVector2 Pivot = { 0.0,0.5 };
	k_spriteRender = NewGO<prefab::CSpriteRender>(1);//���g��
	k_spriteRender->Init(L"sprite/��.dds", 1, 30.0f);
	k_spriteRender->SetPivot(Pivot);//���g���s�{�b�g

	p_spriteRender = NewGO<prefab::CSpriteRender>(0);//�|�e�g
	p_spriteRender->Init(L"sprite/�߂���.dds", 1, 30.0f);
	p_spriteRender->SetPivot(Pivot);//�|�e�g�s�{�b�g

	waku = NewGO<prefab::CSpriteRender>(0);//�g
	waku->Init(L"sprite/hpmp_bar.dds", 500, 50.0f);

	k_spriteRender->SetPosition(k_position);//���g���|�W�V����
	p_spriteRender->SetPosition(p_position);//�|�e�g�|�W�V����
	waku->SetPosition(w_position);
	return true;
}

void ProgressBar::PostRender(CRenderContext& rc)
{
	wchar_t text[256];
	swprintf_s(text, L"�����i%d�i", k);
	m_font.Begin(rc);
	m_font.Draw(
		text,
		{ -580.0,220.0 },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		0.0f,
		1.0f,
		{ 0.0f, 1.0f }
	);

	swprintf_s(text, L"���q�l%d�l", p);
	m_font.Draw(
		text,
		{ -580.0,180.0 },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		0.0f,
		1.0f,
		{ 0.0f, 1.0f }
	);
	m_font.End(rc);
}

void ProgressBar::Update()
{

	CVector3 scale = CVector3::One;
	scale.x *= x;
	k_spriteRender->SetScale(scale);
	p_spriteRender->SetScale(scale);

	x += 3.0;
	y += 2.0;
	if (x >= 500) {
		prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
		CVector3 scale = { 10.0f,1.0f,10.0f };
		effect->SetScale(scale);
		effect->Play(L"effect/Bon.efk");
		effect->SetPosition(effecto);
		x = 0.0f;
	}

	if (y >= 300) {
		prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
		CVector3 scale = { 5.0f,1.0f,5.0f };
		effect->SetScale(scale);
		effect->Play(L"effect/Poteto.efk");
		effect->SetPosition(effe);
		y = 0.0f;
	}
	
	k_spriteRender->SetPosition(k_position);//���g���|�W�V����
	p_spriteRender->SetPosition(p_position);//�|�e�g�|�W�V����
}