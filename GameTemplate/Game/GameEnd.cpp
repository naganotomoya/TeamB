#include "stdafx.h"
#include "Title.h"
#include "GameEnd.h"
GameEnd::GameEnd()
{
}

GameEnd::~GameEnd()
{
	DeleteGO(m_fontkekka);
	DeleteGO(m_fontteikyou);
	DeleteGO(m_fontkazu);
	DeleteGO(m_fontPress);
	DeleteGO(m_hiyoko);
}
bool GameEnd::Start()
{
	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);
	//�������͂��҂�[�I
	m_fontkekka = NewGO<prefab::CFontRender>(0);
	m_fontkekka->SetPivot(CenterPivot);
	m_fontkekka->SetText(L"Result");
	m_fontkekka->SetPosition(kekkapos);
	m_fontkekka->SetColor({ 1.0f,0.0f,0.0f });
	m_fontkekka->SetScale(5.0f);
	//�J���b
	m_fontteikyou = NewGO<prefab::CFontRender>(0);
	m_fontteikyou->SetText(L"�J���b");
	m_fontteikyou->SetPivot(CenterPivot);
	m_fontteikyou->SetPosition(teikyoupos);
	m_fontteikyou->SetColor({ 1.0f,0.0f,0.0f });
	m_fontteikyou->SetScale(2.0f);
	//�����i�̐�
	m_fontkazu = NewGO<prefab::CFontRender>(0);
	m_fontkazu->SetPivot(CenterPivot);
	m_fontkazu->SetScale(5.0f);
	m_fontkazu->SetPosition(kazupos);
	m_fontkazu->SetColor({ 0.0f,0.0f,0.0f });
	//PressAnyKey
	m_fontPress = NewGO<prefab::CFontRender>(0);
	m_fontPress->SetPosition(presspos);
	m_fontPress->SetScale(2.0f);

	//�摜
	m_hiyoko = NewGO<prefab::CSpriteRender>(0);
	m_hiyoko->Init(
		L"sprite/Hiyoko/Fhiyoko.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true
	);
	m_hiyoko->SetPivot({ CenterPivot });
	m_hiyoko->SetPosition(hiyokoPos);
	m_hiyoko->SetRotation(Hanten);
	m_hiyoko->SetScale(hiyokoScale);


	return true;
}
void GameEnd::fontFade()
{
	//fade = 1.0f;
	if (Sfade == true) {
		colorfont.w += 0.01;
		if (colorfont.w >= 1.0f) {
			Sfade = false;
		}
	}
	if (Sfade == false) {
		colorfont.w -= 0.01f;
		if (colorfont.w <= 0.0f) {
			Sfade = true;
		}
	}
	m_fontPress->SetColor(colorfont);
}

void GameEnd::SprintCH()
{
	//�ҋ@���
	if (m_state == Idle) {
		if (timer >= 2.0f) {
			m_state = Big;
		}
	}
	//���ڂ̊g��
	if (m_state == Big) {
		//�摜�̊g�嗦��ς���
		m_hiyoko->SetScale({ 0.1f,0.1f,0.1f });
		if (timer >= 4.0f) {
			m_state = Big2;
		}
	}
	//���ڂ̊g��
	if (m_state == Big2) {
		//�摜�̊g�嗦��ς���
		m_hiyoko->SetScale({ 0.15f,0.15f,0.15f });
		if (timer >= 8.0f) {
			m_hiyoko->SetScale(hiyokoScale);
			//�������ɂ���ĉ摜��ς���
				//����
			if (kazu >= 15) {
				m_state = Sugoi;
			}
			//����
			else if (kazu >= 10) {
				m_state = Futuu;
			}
			//�c�O
			else {
				m_state = Kantan;
			}
		}

	}
	//���ꂼ��̌��ʂɂ�镪��
	if (m_state == Sugoi) {
		//�摜�̕\��
		m_hiyoko->Init(
			L"sprite/Hiyoko/Chiyoko.dds",
			MainCamera().GetWidth(),
			MainCamera().GetHeight(),
			true
		);
	}
	if (m_state == Futuu) {
		//�摜�̕\��
		m_hiyoko->Init(
			L"sprite/Hiyoko/Fhiyoko.dds",
			MainCamera().GetWidth(),
			MainCamera().GetHeight(),
			true
		);
	}
	if (m_state == Kantan) {
		//�摜�̕\��
		m_hiyoko->Init(
			L"sprite/Hiyoko/Whiyoko.dds",
			MainCamera().GetWidth(),
			MainCamera().GetHeight(),
			true
		);
	}
}

void GameEnd::Update()
{
	SprintCH();
	timer += GameTime().GetFrameDeltaTime();
	//�b���߂���܂ł̓����_���ɐ�����\������B
	if (timer <= 8.0f) {
		randamu = rand() % 99;
		swprintf_s(text, L"%02d", randamu);
		m_fontkazu->SetText(text);
	}
	//300�߂����猋�ʂ�\��
	else {
		swprintf_s(text, L"%02d", kazu);
		m_fontkazu->SetText(text);
		//PressAnyKey�ƕ\��
		m_fontPress->SetText(L"PressAnyKey");
		fontFade();
		//�����{�^������������^�C�g���ɖ߂�B
		if (Pad(0).IsPressAnyKey() == true) {
			NewGO<Title>(0, nullptr);
			DeleteGO(this);
		}
	}

}