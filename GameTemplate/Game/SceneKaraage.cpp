#include "stdafx.h"
#include "SceneKaraage.h"
#include "Player.h"
#include "Camera.h"

SceneKaraage::SceneKaraage()
{

}
SceneKaraage::~SceneKaraage()
{
	DeleteGO(m_tong);
	DeleteGO(m_nama);
	DeleteGO(m_abura);
	DeleteGO(m_osara);
	DeleteGO(m_kansei);

}

bool SceneKaraage::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	//�g���O
	m_tong = NewGO<prefab::CSkinModelRender>(0, "tong");
	m_tong->Init(L"modelData/tongs.cmo");
	//���f�����������牺�̂͑�������Ȃ��B
	m_Trotation.SetRotationDeg(CVector3::AxisX, 180.0f);
	m_tong->SetRotation(m_Trotation);
	m_tong->SetScale({ 2.0f,2.0f,2.0f });
	//���̂��炠��
	m_nama = NewGO<prefab::CSkinModelRender>(0, "nama");
	m_nama->Init(L"modelData/KaraageS/Nama.cmo");
	m_Kposition = { 74.0f,0.0f,-5.0f };
	m_StartPos = m_Kposition;
	m_nama->SetPosition(m_Kposition);
	//���M
	m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_osara->SetRotation(m_Srotation);
	m_Sposition = { -60.0f,0.0f,-10.0f };
	m_osara->SetPosition(m_Sposition);

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
	m_abura->SetScale({ 0.05f,0.1f,0.05f });
	m_aburaposition = { -10.0f,0.0f,-20.0f };
	m_abura->SetPosition(m_aburaposition);
	m_abura->SetRotation(Hanten);					//���]��K��
	//�����������炠��
	m_kansei = NewGO<prefab::CSkinModelRender>(0, "kansei");
	m_kansei->Init(L"modelData/KaraageS/Kansei.cmo");
	m_Knseiposition = m_KnseiStartposition;
	m_kansei->SetPosition(m_Knseiposition);

	//m_fontkansei = NewGO<prefab::CFontRender>(0);


	return true;
}

void SceneKaraage::TongMove()
{
	//�v���C���[�̃|�W�V�������g����
	//�g���O�̃|�W�V�����ɂ���
	m_Tposition = m_player->ReturnRPlayerPosition();
	m_Tposition.x += 2.0f;
	m_Tposition.y += 25.0f;
	m_Tposition.z += -3.0f;
	m_tong->SetPosition(m_Tposition);
}

void SceneKaraage::KaraageMove(CVector3& pos)
{
	KTdiff = m_Tposition - pos;
	//���炠���ƃg���O�̋������߂��āA
	//B�{�^����������Ă���Ƃ��B
	//�A�j���[�V�����ǉ��������ɂ��̏������ǉ�
	//�A�j���[�V�������Đ�����Ă��鎞�Ƃ��������ǉ�������
	//����Ƃ��������߂Ȃ��悤�ɏo����͂��B
	if (KTdiff.Length() <= 8.0f &&
		Pad(0).IsPress(enButtonB)) {
		if (pushkara == false) {
			pushkara = true;
		}
		//m_player->Move()�̓v���C���[�N���X�ɒ�`�錾
		//�v���C���[�Ɠ�������������B
		//�����ɍD���ȕϐ�����ꂽ��ǂ��ł��g����B
		if (pushkara == true) {
			m_player->Move(pos);
		}
	}
}

void SceneKaraage::KaraageSyori()
{
	//�����������炠�����Ȃ����
	if (kansei == false) {
		KaraageMove(m_Kposition);
		m_nama->SetPosition(m_Kposition);
		//���炠������x��������
		if (pushkara == true) {
			//�V�[����ς�����A�����ʒu��
			if (Pad(0).IsTrigger(enButtonRB1) ||
				Pad(0).IsTrigger(enButtonLB1)) {
				m_Kposition = m_StartPos;
				m_nama->SetPosition(m_Kposition);
				pushkara = false;
			}
			//���炠���ƃg���O������邩�AB�𗣂�����
			if (KTdiff.Length() >= 20.0f ||
				!Pad(0).IsPress(enButtonB)) {
				KAdiff = m_aburaposition - m_Kposition;
				pushkara = false;
				//���Ƃ̋������߂���Ηg���n�߂�B
				if (KAdiff.Length() <= 35.0f) {
					fry = true;
				}
				//������Ώ����ʒu�֖߂��B
				else {
					m_Kposition = m_StartPos;
					m_nama->SetPosition(m_Kposition);
					pushkara = false;
				}
			}

		}
	}
	//�����������炠���������
	else {
		//OverS += GameTime().GetFrameDeltaTime();
		if (pushkara == false
			&& OverS >= 10) {
			m_Knseiposition = m_KnseiStartposition;
			m_kansei->SetPosition(m_Knseiposition);
			pushkara = false;
			kansei = false;
			OverS = 0;
		}
		//�����������炠���𓮂����悤�ɂ���B
		KaraageMove(m_Knseiposition);
		m_kansei->SetPosition(m_Knseiposition);
		KSdiff = m_Sposition - m_Knseiposition;
		//���炠������x��������A
		if (pushkara == true) {
			//�V�[����ς����炻�̂܂܏���
			if (Pad(0).IsTrigger(enButtonRB1) ||
				Pad(0).IsTrigger(enButtonLB1)) {
				m_Knseiposition = m_KnseiStartposition;
				m_kansei->SetPosition(m_Knseiposition);
				OverS = 0;
				pushkara = false;
				kansei = false;
			}
			//���炠���ƃg���O������邩�AB�𗣂�����
			if (KTdiff.Length() >= 20.0f ||
				!Pad(0).IsPress(enButtonB)) {
				KSdiff = m_Sposition - m_Knseiposition;
				//���M�̏�ŗ�������
				//�������𑝂₷�B
				if (KSdiff.Length() <= 20.0f) {
					pushkara = false;
					m_Knseiposition = m_KnseiStartposition;
					m_kansei->SetPosition(m_Knseiposition);
					OverS = 0;
					KanseiKosuu++;
					kansei = false;
				}
				//�������
				else {
					//�������͑��₳���ɏ����B
					m_Knseiposition = m_KnseiStartposition;
					m_kansei->SetPosition(m_Knseiposition);
					OverS = 0;
					pushkara = false;
					kansei = false;
				}
			}

		}
	}
}

void SceneKaraage::FrySyori()
{
	KAdiff = m_aburaposition - m_Kposition;
	//���Ƃ̋���������Ă��܂�����B
	if (KAdiff.Length() >= 35.0f) {
		m_Kposition = m_StartPos;
		m_nama->SetPosition(m_Kposition);
		fry = false;
		pushkara = false;
		KaraageS = 0.0f;
	}
	if (KaraageS >= 10) {
		//�����������炠�����o��
		m_Knseiposition = m_Kposition;
		m_kansei->SetPosition(m_Knseiposition);
		kansei = true;

		m_Kposition = m_StartPos;
		m_nama->SetPosition(m_Kposition);
		fry = false;
		pushkara = false;
		KaraageS = 0.0f;
	}
}

void SceneKaraage::Update()
{
	//���̃V�[�������炠���̏����Ȃ�A������
		//�J�[�\����ReturnMowScene�Ɏ����Ă�������ǂ̔ԍ����ǂ̃V�[�����킩��܂��B
	nowscene = m_camera->ReturnNowScene();
	if (nowscene == 0) {
		m_player->RgripAnimation();
		TongMove();
		KaraageSyori();
	}
	if (Pad(0).IsTrigger(enButtonRB1) ||
		Pad(0).IsTrigger(enButtonLB1)) {
		m_player->RopenAnimation();
	}
	//�ϐ��̓V�[�������炠���łȂ��Ă�������
	if (fry == true) {
		//�����KaraageS�ɕb���𑫂���
		KaraageS += GameTime().GetFrameDeltaTime();
		FrySyori();
	}
	if (kansei == true) {
		OverS += GameTime().GetFrameDeltaTime();
	}
	//m_nama->SetEmissionColor({ 1.0f,1.0f,1.0f });
	/*CVector3 colar;
	colar.x = 0.0f;
	colar.y = 0.0f;
	colar.z = 0.0f;
	swprintf_s(text, L"%02d", KanseiKosuu);
	m_fontkansei->SetText(text);
	m_fontkansei->SetColor(colar);*/
}