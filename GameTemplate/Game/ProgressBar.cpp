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
	k_spriteRender = NewGO<prefab::CSpriteRender>(0);
	k_spriteRender->SetPivot(Pivot);
	
	
	return true;
}

void ProgressBar::Update()
{
	k_spriteRender->Init(L"sprite/Ô.dds", x, 80.0f);
	x += 5;
	if (x >= 500) {
		prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
		CVector3 scale = { 10.0f,1.0f,10.0f };
		effect->SetScale(scale);
		effect->Play(L"effect/Bon.efk");
		effect->SetPosition(k_position);
		x = 0.0f;
	}
}