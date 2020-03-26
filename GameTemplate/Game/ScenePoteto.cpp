#include "stdafx.h"
#include "ScenePoteto.h"
#include "Player.h"
#include "Camera.h"

ScenePoteto::ScenePoteto()
{
}

ScenePoteto::~ScenePoteto()
{
	DeleteGO(m_Poteto);
	DeleteGO(m_Flyer);
	DeleteGO(m_osara);
	DeleteGO(m_abura);
}

bool ScenePoteto::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	//�|�e�g
	m_Poteto = NewGO<prefab::CSkinModelRender>(0, "Poteto");
	m_Poteto->Init(L"modelData/Poteto/poteto.cmo");
	m_Pposition = { -1230.0f,0.0f,0.0f};
	m_Poteto->SetPosition(m_Pposition);
	//�t���C���[
	m_Flyer = NewGO<prefab::CSkinModelRender>(1, "Flyer");
	m_Flyer->Init(L"modelData/Poteto/huraiya-4.cmo");
	FlyQuater.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_Flyer->SetRotation(FlyQuater);
	m_Fposition = { -1280.0f,0.0f,-20.0f };
	m_Flyer->SetPosition(m_Fposition);
	//���M
	m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_osara->SetRotation(m_Srotation);
	m_Oposition = { -1340.0f,0.0f,0.0f };
	m_osara->SetPosition(m_Oposition);

	//��
	//2D�\������Ƃ����̂܂܂��ƂłȂ��Ǝv������3D�\���ɂ��Ĕ��]�����Ă��������B
	m_abura = NewGO<prefab::CSpriteRender>(0);
	m_abura->Init(
		L"sprite/Phaikei/Abura.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true	//3D�\��
	);
	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//���]
	m_abura->SetScale({ 0.02f,0.0375f,0.05f });
	m_aburaposition = { -1281.5f,14.6f,1.5f };
	m_abura->SetPosition(m_aburaposition);
	m_abura->SetRotation(Hanten);					//���]��K��

	
	
	return true;
}


void ScenePoteto::Update()
{
	//�Ȃɂ��Ȃ����
	if (m_state == State_None) {
		if (Pad(0).IsPress(enButtonB)) {
			m_state = State_PickPoteto;
		}
	}

	//�|�e�g�������Ă�����
	else if (m_state == State_PickPoteto) {
		//�A��ƃ|�e�g�̋������߂��Ȃ�����A

		//�v���C���[�̎�ƃ|�e�g�̋����𑪒�
		PPdiff = m_player->ReturnRPlayerPosition() - m_Pposition;
		//�v���C���[�̎�̓����蔻��v�Z
		float len = PPdiff.Length();
		//�����R�O�ȉ���B�{�^���������ꂽ��
		if (len <= 30.0f && Pad(0).IsPress(enButtonB)) {
			m_player->Move(m_Pposition);
			m_Poteto->SetPosition(m_Pposition);
		}

		//�|�e�g�Ƃ��M�̋������߂��Ȃ�����
		PTdiff = m_Pposition - m_Oposition;
		//�����蔻��
		len = PTdiff.Length();
		//IsActive()��DeleteGO���ꂽ��False�@NewGO���ꂽ��True�Ȃ�t���O
		if (len <= 20.0f && !Pad(0).IsPress(enButtonB) && m_Poteto->IsActive() == true) {
			bool Ispoteto = true;
			//���M�ƃ|�e�g�̋�����20.0�ȉ���B�{�^����������ĂȂ��āA�|�e�g�̃A�N�e�B�u��True�Ȃ�
			m_state = State_TranlateFlyer;
		}
		//�|�e�g�Ɩ��̋������߂��Ȃ�����
		APdiff = m_Pposition - m_aburaposition;
		float Len = APdiff.Length();
		if (Len <= 20.0f && !Pad(0).IsPress(enButtonB)) {
			PoteFly += GameTime().GetFrameDeltaTime();
			if (PoteFly >= 4) {
				//�g�����ă|�e�g��NewGO����
			}
		}
	}

	//�|�e�g�𐷂�t������
	else if (m_state == State_TranlateFlyer) {
		//�X�e�[�g������t�����ԂȂ�
		//�|�e�g�̃I�u�W�F�N�g���폜
		DeleteGO(m_Poteto);
		//�X�e�[�g���������ĂȂ���ԂɕύX
		m_state = State_None;
	}

	//else if (m_state == State_TranlateFlyer) {
		//�|�e�g�Ƃ��M�̋������߂��Ȃ�����
		//PTdiff = m_Pposition - m_Oposition;
		//float len = PTdiff.Length();
		//if (PTdiff.Length() <= 20.0f && !Pad(0).IsPress(enButtonB)) {
		//	int a = 0;
		//	if (m_Poteto != nullptr) {
		//		DeleteGO(m_Poteto);
		//		m_Poteto = nullptr;
		//	}

		//}
	//}


}