#include "stdafx.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar()
{
}

ProgressBar::~ProgressBar()
{
	DeleteGO(k_spriteRender);
	DeleteGO(p_spriteRender);
	DeleteGO(waku);
	DeleteGO(waku_01);
}

bool ProgressBar::Start()
{
	CVector2 Pivot = { 0.0,0.5 };
	k_spriteRender = NewGO<prefab::CSpriteRender>(1);//唐揚げ
	k_spriteRender->Init(L"sprite/赤.dds", 1, 30.0f);
	k_spriteRender->SetPivot(Pivot);//唐揚げピボット

	p_spriteRender = NewGO<prefab::CSpriteRender>(1);//ポテト
	p_spriteRender->Init(L"sprite/悲しみ.dds", 1, 30.0f);
	p_spriteRender->SetPivot(Pivot);//ポテトピボット

	waku = NewGO<prefab::CSpriteRender>(0);//枠
	waku->Init(L"sprite/hpmp_bar.dds", 500, 50.0f);

	waku_01 = NewGO<prefab::CSpriteRender>(0);//枠
	waku_01->Init(L"sprite/hpmp_bar.dds", 500, 50.0f);

	k_spriteRender->SetPosition(k_position);//唐揚げポジション
	p_spriteRender->SetPosition(p_position);//ポテトポジション
	waku->SetPosition(w_position);//唐揚げ枠
	waku_01->SetPosition(w01_position);//ポテト枠
	return true;
}

void ProgressBar::PostRender(CRenderContext& rc)
{
	wchar_t text[256];
	swprintf_s(text, L"完成品%d品", k);
	m_font.Begin(rc);
	m_font.Draw(
		text,
		{ -580.0,200.0 },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		0.0f,
		1.0f,
		{ 0.0f, 1.0f }
	);

	swprintf_s(text, L"お客様%d人", p);
	m_font.Draw(
		text,
		{ -580.0,150.0 },
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
	
	if (x >= 500) {
		/////唐揚げエフェクト/////
		prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
		CVector3 scale = { 3.0f,1.0f,3.0f };
		effect->SetScale(scale);
		effect->Play(L"effect/Bon.efk");
		effect->SetPosition(effecto);
		/////////////////////////

		/////ポテトエフェクト/////
		prefab::CEffect* effectoo = NewGO<prefab::CEffect>(0);
		CVector3 scales = { 5.0f,1.0f,5.0f };
		effectoo->SetScale(scales);
		effectoo->Play(L"effect/Poteto.efk");
		effectoo->SetPosition(effe);
		/////////////////////////
		x = 0.0f;
	}

	//if (p > 5) {								//お客様が５人超えたら
	//	bgm = NewGO<prefab::CSoundSource>(0);	//CSoundSourceのインスタンスを作成。
	//	bgm->Init("sound/normalBGM.wav");		//音声ファイルをロード。
	//	bgm->Play(true);
	//}
	
	k_spriteRender->SetPosition(k_position);//唐揚げポジション
	p_spriteRender->SetPosition(p_position);//ポテトポジション
}