#include "stdafx.h"
#include "SceneMorituke.h"
#include "Camera.h"
#include "Player.h"
SceneMorituke::SceneMorituke()
{
}
SceneMorituke::~SceneMorituke()
{
	DeleteGO(m_kyabetu);
	DeleteGO(m_houtyou);
	DeleteGO(m_manaita);
	DeleteGO(m_cutOkyabetu);
}

bool SceneMorituke::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	//�L���x�c
	m_kyabetu = NewGO<prefab::CSkinModelRender>(0, "kyabetu");
	m_kyabetu->Init(L"modelData/MoritukeS/Kyabetu3.cmo");
	m_kyabetu->SetScale(m_Kscal);
	m_kyabetu->SetPosition(m_kyabetupos);
	//�
	m_houtyou = NewGO<prefab::CSkinModelRender>(0, "houtyou");
	m_houtyou->Init(L"modelData/MoritukeS/houtyou.cmo");
	m_houtyou->SetPosition(m_houtyoupos);
	m_houtyou->SetScale({ 3.0f,3.0f,3.0f });
	m_houtyouRotation.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_houtyou->SetRotation(m_houtyouRotation);
	//���M
	m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_osara->SetRotation(m_Srotation);
	m_osara->SetPosition({ -3900.0f,0.0f,-20.0f });
	//�܂Ȕ�
	m_manaita = NewGO<prefab::CSpriteRender>(0);
	m_manaita->Init(
		L"sprite/Phaikei/Manaita.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true	//3D�\��
	);
	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//���]
	m_manaita->SetScale({ 0.05f,0.06f,0.05f });
	m_manaita->SetPosition(m_manaitapos);
	m_manaita->SetRotation(Hanten);					//���]��K��
	////�؂����L���x�c
	//m_cutkyabetu = NewGO<prefab::CSpriteRender>(0);
	//m_cutkyabetu->Init(
	//	L"sprite/Phaikei/Cutkyabetu.dds",
	//	MainCamera().GetWidth(),
	//	MainCamera().GetHeight(),
	//	true	//3D�\��
	//);
	//m_cutkyabetu->SetScale(m_Cutscal);//0.02
	//m_cutkyabetu->SetPosition(m_cutkyabetupos);
	//m_cutkyabetu->SetRotation(Hanten);					//���]��K��
	//m_cutkyabetu->SetPivot({ 1.0f,0.5f });
	//���M�̂���ׂ�
	m_cutOkyabetu = NewGO<prefab::CSpriteRender>(0);
	m_cutOkyabetu->Init(
		L"sprite/Karaage/CutKyabetu.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true	//3D�\��
	);
	m_cutOkyabetu->SetScale(m_CutOsara);
	m_cutOkyabetu->SetPosition(m_cutosarakyabetupos);
	m_cutOkyabetu->SetRotation(Hanten);					//���]��K��
	m_cutOkyabetu->SetPivot({ 0.5f,0.5f });

	return true;
}

void SceneMorituke::Move()
{
	if (Pad(0).IsTrigger(enButtonB)) {
		m_player->setRHandZ(0.0f);
	}
	//�v���C���[�̃|�W�V�������g���ĕ�𓮂����B
	m_houtyoupos = m_player->ReturnRPlayerPosition();
	//m_houtyoupos.x +=
	m_houtyoupos.y += 20.0f;
	m_houtyoupos.z -= 5.0f;
	m_houtyou->SetPosition(m_houtyoupos);
}

void SceneMorituke::Cut()
{
	//��Ƃ܂Ȕ̋������߂���
	//B�{�^������������
	KMdiff = m_manaitapos - m_houtyoupos;
	if (KMdiff.Length() <= 50.0f) {
		if (Pad(0).IsTrigger(enButtonB)) {
			//m_player->setRHandZ(0.0f);
			//�J�b�g�J�E���g���v���X����B
			Cutcount--;
			//�L���x�c�̊g�嗦��ς���B
			m_Kscal.x -= 1.0f / CT;
			//m_Cutscal.x += 0.02f / CT;
			//���M�ɐ�����L���x�c�̊g�嗦
			m_CutOsara.x += CutkyabeXScal / (CT / 2);
			m_CutOsara.y += CutkyabeXScal / (CT / 2);
			//�L���x�c�����M�����ς��ɂȂ�����A
			//0�ɂ���B
			if (m_CutOsara.x >= CutkyabeXScal ||
				m_CutOsara.y >= CutkyabeXScal) {
				m_CutOsara.x = 0.0f;
				m_CutOsara.y = 0.0f;
				//�������𑝂₷�B
				Kansei++;
			}
			//�J�b�g�J�E���g��0�ɂȂ�����
			if (Cutcount <= 0) {
				//�g�嗦��߂��B
				m_Kscal.x = 1.0f;
				//m_Cutscal.x = 0.0f;
				//�J�b�g�J�E���g��30�ɂ��āA
				Cutcount = 30;
			}
		}
		m_kyabetu->SetScale(m_Kscal);
		//m_cutkyabetu->SetScale(m_Cutscal);
		m_cutOkyabetu->SetScale(m_CutOsara);
	}
}

void SceneMorituke::Update()
{
	nowscene = m_camera->ReturnNowScene();
	if (nowscene == 3) {
		m_player->setRHandZ(7.0f);
		m_player->RgripAnimation();
		Move();
		Cut();
	}
	if (Pad(0).IsTrigger(enButtonRB1) ||
		Pad(0).IsTrigger(enButtonLB1)) {
		m_player->setRHandZ(0.0f);
	}
}