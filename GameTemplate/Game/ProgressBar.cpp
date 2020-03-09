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
	k_spriteRender = NewGO<prefab::CSpriteRender>(1);//���g��
	k_spriteRender->Init(L"sprite/��.dds", 1, 30.0f);
	k_spriteRender->SetPivot(Pivot);//���g���s�{�b�g

	p_spriteRender = NewGO<prefab::CSpriteRender>(1);//�|�e�g
	p_spriteRender->Init(L"sprite/�߂���.dds", 1, 30.0f);
	p_spriteRender->SetPivot(Pivot);//�|�e�g�s�{�b�g

	waku = NewGO<prefab::CSpriteRender>(0);//�g
	waku->Init(L"sprite/hpmp_bar.dds", 500, 50.0f);

	waku_01 = NewGO<prefab::CSpriteRender>(0);//�g
	waku_01->Init(L"sprite/hpmp_bar.dds", 500, 50.0f);

	k_spriteRender->SetPosition(k_position);//���g���|�W�V����
	p_spriteRender->SetPosition(p_position);//�|�e�g�|�W�V����
	waku->SetPosition(w_position);//���g���g
	waku_01->SetPosition(w01_position);//�|�e�g�g
	return true;
}

void ProgressBar::PostRender(CRenderContext& rc)
{
	wchar_t text[256];
	swprintf_s(text, L"�����i%d�i", k);
	m_font.Begin(rc);
	m_font.Draw(
		text,
		{ -580.0,200.0 },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
		0.0f,
		1.0f,
		{ 0.0f, 1.0f }
	);

	swprintf_s(text, L"���q�l%d�l", p);
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
		/////���g���G�t�F�N�g/////
		prefab::CEffect* effect = NewGO<prefab::CEffect>(0);
		CVector3 scale = { 3.0f,1.0f,3.0f };
		effect->SetScale(scale);
		effect->Play(L"effect/Bon.efk");
		effect->SetPosition(effecto);
		/////////////////////////

		/////�|�e�g�G�t�F�N�g/////
		prefab::CEffect* effectoo = NewGO<prefab::CEffect>(0);
		CVector3 scales = { 5.0f,1.0f,5.0f };
		effectoo->SetScale(scales);
		effectoo->Play(L"effect/Poteto.efk");
		effectoo->SetPosition(effe);
		/////////////////////////
		x = 0.0f;
	}

	//if (p > 5) {								//���q�l���T�l��������
	//	bgm = NewGO<prefab::CSoundSource>(0);	//CSoundSource�̃C���X�^���X���쐬�B
	//	bgm->Init("sound/normalBGM.wav");		//�����t�@�C�������[�h�B
	//	bgm->Play(true);
	//}
	
	k_spriteRender->SetPosition(k_position);//���g���|�W�V����
	p_spriteRender->SetPosition(p_position);//�|�e�g�|�W�V����
}