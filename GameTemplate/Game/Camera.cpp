#include "stdafx.h"
#include "Camera.h"
#include "tkEngine/light/tkDirectionLight.h"

Camera::Camera()
{

}

Camera::~Camera()
{
	DeleteGO(m_spriteKaraage);
	DeleteGO(m_spritePoteto);
	DeleteGO(m_spriteDrink);
	DeleteGO(m_spriteMorituke);
	DeleteGO(m_spriteAraimono);
	DeleteGO(m_spriteKaikei);
	DeleteGO(lig);
}
bool Camera::Start()
{
	/*�e�V�[���̏��*/
	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);
	//����g��
	scene[Karaage].TxPos = 0.0f;
	scene[Karaage].PxPos = 0.0f;
	m_spriteKaraage = NewGO<prefab::CSpriteRender>(0);
	m_spriteKaraage->Init(
		L"sprite/Phaikei/Karaageheikei.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true
	);
	m_spriteKaraage->SetPosition({ scene[Karaage].TxPos,0.0f,-520.0f });
	m_spriteKaraage->SetRotation(Hanten);
	//�|�e�g
	scene[Poteto].TxPos = scene[Poteto - 1].TxPos - CX;
	scene[Poteto].PxPos = scene[Poteto - 1].TxPos - CX;
	m_spritePoteto = NewGO<prefab::CSpriteRender>(0);
	m_spritePoteto->Init(
		L"sprite/Phaikei/Poteto.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true
	);
	m_spritePoteto->SetPosition({ scene[Poteto].TxPos,0.0f,-520.0f });
	m_spritePoteto->SetRotation(Hanten);
	//�h�����N
	scene[Drink].TxPos = scene[Drink - 1].TxPos - CX;
	scene[Drink].PxPos = scene[Drink - 1].TxPos - CX;
	m_spriteDrink = NewGO<prefab::CSpriteRender>(0);
	m_spriteDrink->Init(
		L"sprite/Phaikei/DrinkHaikei.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true
	);
	m_spriteDrink->SetPosition({ scene[Drink].TxPos,0.0f,-520.0f });
	m_spriteDrink->SetRotation(Hanten);
	//����t��
	scene[Morituke].TxPos = scene[Morituke - 1].TxPos - CX;
	scene[Morituke].PxPos = scene[Morituke - 1].TxPos - CX;
	m_spriteMorituke = NewGO<prefab::CSpriteRender>(0);
	m_spriteMorituke->Init(
		L"sprite/Phaikei/moritukehaikei.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true
	);
	m_spriteMorituke->SetPosition({ scene[Morituke].TxPos,0.0f,-520.0f });
	m_spriteMorituke->SetRotation(Hanten);
	//�􂢕�
	scene[Araimono].TxPos = scene[Araimono - 1].TxPos - CX;
	scene[Araimono].PxPos = scene[Araimono - 1].TxPos - CX;
	m_spriteAraimono = NewGO<prefab::CSpriteRender>(0);
	m_spriteAraimono->Init(
		L"sprite/Phaikei/Araimono.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true
	);
	m_spriteAraimono->SetPosition({ scene[Araimono].TxPos,0.0f,-520.0f });
	m_spriteAraimono->SetRotation(Hanten);
	//��v
	scene[Kaikei].TxPos = scene[Kaikei - 1].TxPos - CX;
	scene[Kaikei].PxPos = scene[Kaikei - 1].TxPos - CX;
	m_spriteKaikei = NewGO<prefab::CSpriteRender>(0);
	m_spriteKaikei->Init(
		L"sprite/Phaikei/Kaikei.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true
	);
	m_spriteKaikei->SetPosition({ scene[Kaikei].TxPos,0.0f,-520.0f });
	m_spriteKaikei->SetRotation(Hanten);
	/*--------------------------------*/
		//�J������ݒ�B
	MainCamera().SetTarget({ scene[Karaage].TxPos, 0.0f, 0.0f });
	MainCamera().SetPosition({ scene[Karaage].PxPos, 0.0f, 100.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(1000.0f);
	MainCamera().Update();

	//���C�g�̐ݒ�
	lig = NewGO<prefab::CDirectionLight>(0);
	//���C�g�̕�����ݒ�B
	//lig->SetDirection({ 0.1f, 0.1f, 0.0f });
	//���C�g�̐F��ݒ�B
	lig->SetColor({ 10.5f, 10.5f, 10.5f, 10.0f });
	LightManager().SetAmbientLight({ 5.0f, 5.0f, 5.0f });

	return true;
}

void Camera::Update()
{
	//�E����������
	if (Pad(0).IsTrigger(enButtonRB1)) {
		//��ԍŌ�̃V�[���̏ꍇ�A�ŏ��ֈړ��B
		if (NowScene == SceneNum - 1) {
			NowScene = 0;
		}
		//�E�̃|�W�V�����ֈړ�
		else {
			NowScene++;
		}
		//�J�����̐ݒ�
		MainCamera().SetTarget({ scene[NowScene].TxPos, 0.0f, 0.0f });
		MainCamera().SetPosition({ scene[NowScene].PxPos, 0.0f, 100.0f });
		//m_spriteKaraage->SetPosition({ scene[NowScene].TxPos,0.0f,-500.0f });
	}

	//������������
	if (Pad(0).IsTrigger(enButtonLB1)) {
		//��ԍŏ��̃V�[���̏ꍇ�A�Ō�ֈړ��B
		if (NowScene == 0) {
			NowScene = SceneNum - 1;
		}
		//���̃|�W�V�����ֈړ�
		else {
			NowScene--;
		}
		//�J�����̐ݒ�
		MainCamera().SetTarget({ scene[NowScene].TxPos, 0.0f, 0.0f });
		MainCamera().SetPosition({ scene[NowScene].PxPos, 0.0f, 100.0f });
		//m_spriteKaraage->SetPosition({ scene[NowScene].TxPos,0.0f,-500.0f });
	}

	MainCamera().Update();
}