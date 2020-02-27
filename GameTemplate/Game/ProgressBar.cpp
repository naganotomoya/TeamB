#include "stdafx.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar()
{
}

ProgressBar::~ProgressBar()
{
	DeleteGO(k_spriteRender);
}

bool ProgressBar::Start()
{
	CVector2 Pivot = { 0.0,0.5 };
	k_spriteRender = NewGO<prefab::CSpriteRender>(0);//���g��
	k_spriteRender->SetPivot(Pivot);//���g���s�{�b�g

	p_spriteRender = NewGO<prefab::CSpriteRender>(0);//�|�e�g
	p_spriteRender->SetPivot(Pivot);//�|�e�g�s�{�b�g



	return true;
}

void ProgressBar::Update()
{
	k_spriteRender->Init(L"sprite/��.dds", x, 30.0f);
	p_spriteRender->Init(L"sprite/�߂���.dds", y, 30.0f);
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
	
	k_spriteRender->SetPosition(k_position);
	p_spriteRender->SetPosition(p_position);
}