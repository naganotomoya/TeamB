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
	DeleteGO(m_KanseiPoteto);
	DeleteGO(m_Flyer);
	DeleteGO(m_osara);
	DeleteGO(m_abura);
	//DeleteGO(piyo);
}

bool ScenePoteto::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	//���|�e�g
	m_Poteto = NewGO<prefab::CSkinModelRender>(0, "Poteto");
	m_Poteto->Init(L"modelData/icePote/Poteto1.cmo");
	m_Pposition = { -1208.0f,0.0f,0.0f};
	m_Poteto->SetPosition(m_Pposition);
	//�|�e�g
	m_KanseiPoteto = NewGO<prefab::CSkinModelRender>(0, "KanseiPoteto");
	m_KanseiPoteto->Init(L"modelData/Poteto/poteto.cmo");
	m_KanseiPoteto->SetPosition(m_Kanseiposition);
	
	//�t���C���[
	m_Flyer = NewGO<prefab::CSkinModelRender>(1, "Flyer");
	m_Flyer->Init(L"modelData/Poteto/huraiya-4.cmo");
	FlyQuater.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_Flyer->SetRotation(FlyQuater);
	m_Flyer->SetScale({ 1.5f,1.25f,1.25f });
	m_Fposition = { -1275.0f,-20.0f,-30.0f };
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
	m_abura->SetScale({ 0.031f,0.05f,0.05f });
	m_aburaposition = { -1278.0f,4.0f,-5.0f };
	m_abura->SetPosition(m_aburaposition);
	m_abura->SetRotation(Hanten);					//���]��K��


	piyo = NewGO<prefab::CSoundSource>(0);
	piyo->Init(L"sound/SE/age.wav");
	piyo->Play(true);
	piyo->SetVolume(0.0f);
	
	return true;
}


void ScenePoteto::Update()
{
	PoteFly += GameTime().GetFrameDeltaTime();//�����Ԃł��B
	nowscene = m_camera->ReturnNowScene();
	if (nowscene == 1) {
		//B�������Ă���Ԏ��������ꍇ�̏���
		if (Pad(0).IsPress(enButtonB)) {
			m_player->RgripAnimation();//����
		}
		else {
			m_player->RopenAnimation();//�J��
		}
	}

	//�Ȃɂ��Ȃ����
	if (m_state == State_None) {
		if (Pad(0).IsPress(enButtonB)) {
			m_state = State_PickPoteto;
		}
	}

	//�|�e�g�������Ă�����
	else if (m_state == State_PickPoteto) {
		//�v���C���[�̎�ƃ|�e�g�̋����𑪒�
		PPdiff = m_player->ReturnRPlayerPosition() - m_Pposition;
		//�v���C���[�̎�̓����蔻��v�Z
		float len = PPdiff.Length();
		//�����R�O�ȉ���B�{�^���������ꂽ��
		if (len <= 30.0f && Pad(0).IsPress(enButtonB)) {
			m_player->Move(m_Pposition);
			if (Nama == true) {
				m_Poteto->SetPosition(m_Pposition);
			}
			else {
				m_KanseiPoteto->SetPosition(m_Pposition);

			}
			
		}

		//�|�e�g�Ƃ��M�̋������߂��Ȃ�����
		PTdiff = m_Pposition - m_Oposition;
		//�����蔻��
		len = PTdiff.Length();

		//�|�e�g�Ɩ��̋������߂��Ȃ�����
		APdiff = m_Pposition - m_aburaposition;
		//�����蔻��
		float Len = APdiff.Length();

		//IsActive()��DeleteGO���ꂽ��False�@NewGO���ꂽ��True�Ȃ�t���O
		if (len <= 20.0f && !Pad(0).IsPress(enButtonB) && m_KanseiPoteto->IsActive() == true) {
			bool Ispoteto = true;
			//���M�ƃ|�e�g�̋�����20.0�ȉ���B�{�^����������ĂȂ��āA�|�e�g�̃A�N�e�B�u��True�Ȃ�
			m_state = State_TranlateFlyer;
		}

		//�|�e�g�Ɩ��̋������߂��Ȃ�����g���Ă����ԂɃ��[�v
		else if (Len <= 20.0f && !Pad(0).IsPress(enButtonB) && m_Poteto->IsActive() == true) {
			PoteFly = 0.0f;
			m_state = State_oilinput;
		}
	
	}

	//�|�e�g��g���Ă�����
	else if (m_state == State_oilinput) {
		//�g���Ă���Ƃ���BGM
		piyo->SetVolume(1.0f);
		if (PoteFly >= 1 ) {
			//���|�e�Ƃ��폜����B
			//DeleteGO(m_Poteto);
			m_Poteto->SetScale({ 0.0f,0.0f,0.0f });
			Nama = false;				//���̃|�e�g���Ȃ��Ȃ���.
			//�g�����ă|�e�g�𐶐�
			//m_KanseiPoteto = NewGO<prefab::CSkinModelRender>(0, "KanseiPoteto");
			//m_KanseiPoteto->Init(L"modelData/Poteto/poteto.cmo");
			m_KanseiPoteto->SetScale({ 1.0f,1.0f,1.0f });
			Fried = true;				//�|�e�g�������B
			//�g�����ă|�e�g��NewGO����
			m_KanseiPoteto->SetPosition(m_Pposition);
			//�g�����|�e�g����������
			m_state = State_None;
		}
	}

	//�|�e�g�𐷂�t������
	else if (m_state == State_TranlateFlyer) {
		piyo->SetVolume(0.0f);
		//�X�e�[�g������t�����ԂȂ�
		//�|�e�g�̃I�u�W�F�N�g���폜
		//DeleteGO(m_KanseiPoteto);
		m_KanseiPoteto->SetScale({ 0.0f,0.0f,0.0f });
		//���|�e�g�𐶐�
		//m_Poteto = NewGO<prefab::CSkinModelRender>(0, "Poteto");
		//m_Poteto->Init(L"modelData/icePote/Poteto1.cmo");

		//���������|�e�Ƃ̐�
		PotetoKansei++;

		m_Poteto->SetScale({ 1.0f,1.0f,1.0f });
		m_Pposition = InitialPosition;
		m_Poteto->SetPosition(m_Pposition);
		Nama = true;				//���̃|�e�g������B
		//�X�e�[�g���������ĂȂ���ԂɕύX
		m_state = State_None;
	}

}