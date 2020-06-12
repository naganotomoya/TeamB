#include "stdafx.h"
#include "SceneKaraage.h"
#include "Player.h"
#include "Camera.h"
#include "KaraageGenerator.h"

SceneKaraage::SceneKaraage()
{

}
SceneKaraage::~SceneKaraage()
{
	DeleteGO(m_tong);
	//DeleteGO(m_nama);
	DeleteGO(m_abura);
	DeleteGO(m_osara);
	//DeleteGO(m_kansei);	
	QueryGOs<KaraageGenerator>("karaagegenerator",
		[](KaraageGenerator* karaagegenerator)->bool {
			DeleteGO(karaagegenerator);
			return true;
		});

}

bool SceneKaraage::Start()
{
	m_gene = NewGO<KaraageGenerator>(0, "karaagegenerator");
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	m_gene = FindGO<KaraageGenerator>("karaagegenerator");
	//�g���O
	m_tong = NewGO<prefab::CSkinModelRender>(0, "tong");
	m_tong->Init(L"modelData/tongs.cmo");
	//���f�����������牺�̂͑�������Ȃ��B
	m_Trotation.SetRotationDeg(CVector3::AxisX, 180.0f);
	m_tong->SetRotation(m_Trotation);
	m_tong->SetScale({ 2.0f,2.0f,2.0f });
	////���̂��炠��
	//m_nama = NewGO<prefab::CSkinModelRender>(0, "nama");
	//m_nama->Init(L"modelData/KaraageS/Nama.cmo");
	//m_Kposition = { 74.0f,0.0f,-5.0f };
	//m_StartPos = m_Kposition;
	//m_nama->SetPosition(m_Kposition);
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
	m_abura->SetScale({ 0.04f,0.08f,0.05f });
	m_aburaposition = { -8.5f,0.0f,-2.5f };
	m_abura->SetPosition(m_aburaposition);
	m_abura->SetRotation(Hanten);					//���]��K��
	m_abura->SetMulColor({ 1.0f,1.0f,1.0f,0.8f });
	////�����������炠��
	//m_kansei = NewGO<prefab::CSkinModelRender>(0, "kansei");
	//m_kansei->Init(L"modelData/KaraageS/Kansei.cmo");
	//m_Knseiposition = m_KnseiStartposition;
	//m_kansei->SetPosition(m_Knseiposition);

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

//void SceneKaraage::KaraageMove(CVector3& pos, float dif)
//{
//	KTdiff = m_Tposition - pos;
//	//���炠���ƃg���O�̋������߂��āA
//	//B�{�^����������Ă���Ƃ��B
//	//�A�j���[�V�����ǉ��������ɂ��̏������ǉ�
//	//�A�j���[�V�������Đ�����Ă��鎞�Ƃ��������ǉ�������
//	//����Ƃ��������߂Ȃ��悤�ɏo����͂��B
//	if (KTdiff.Length() <= dif &&
//		Pad(0).IsPress(enButtonB)) {
//		//m_player->Move()�̓v���C���[�N���X�ɒ�`�錾
//		//�v���C���[�Ɠ�������������B
//		//�����ɍD���ȕϐ�����ꂽ��ǂ��ł��g����B
//		m_player->Move(pos);
//	}
//}

//void SceneKaraage::KaraageSyori()
//{
//	/*�����ʒu�A�ҋ@*/
//	if (m_state == StateIdle) {
//		//������Ɗ����������炠���������|�W�ɖ߂��B
//		m_Kposition = m_StartPos;
//		m_Knseiposition = m_KnseiStartposition;
//		//���炠���g���O�̋���
//		KTdiff = m_Tposition - m_Kposition;
//		//���炠���ƃg���O���߂��āAB��������Ă���ƁA
//		//Statepush�Ɉړ�
//		if (KTdiff.Length() <= 8.0f &&
//			Pad(0).IsPress(enButtonB)) {
//			m_state = Statepush;
//		}
//	}
//	/*�����玝�������*/
//	if (m_state == Statepush) {
//		//�����炠���𓮂����B
//		KaraageMove(m_Kposition, 8.0f);
//		//�V�[����ς�����A�����ʒu��
//		if (Pad(0).IsTrigger(enButtonRB1) ||
//			Pad(0).IsTrigger(enButtonLB1)) {
//			m_state = StateIdle;
//		}
//		//B�𗣂������A���Ƌ߂���Ύ��̏���
//		if (!Pad(0).IsPress(enButtonB) ||
//			KTdiff.Length() >= 10.0f) {
//			//���炠���Ɩ��̋���
//			KAdiff = m_aburaposition - m_Kposition;
//			if (KAdiff.Length() <= 35.0f) {
//				m_state = Statefry;
//			}
//			//������Ώ����ʒu�֖߂��B
//			else {
//				m_state = StateIdle;
//			}
//		}
//	}
//	/*�g������*/
//	if (m_state == Statefry) {
//		//�w�肵���b���o������
//		if (KaraageS <= 0.0f) {
//			//�����������炠�����o��
//			m_Knseiposition = m_Kposition;
//			m_Kposition = m_StartPos;
//			//�b���������ɖ߂��āAStatekansei�Ɉړ�
//			KaraageS = 10.0f;
//			m_state = Statekansei;
//		}
//	}
//	/*�����������炠����������*/
//	if (m_state == Statekansei) {
//		//���ꂼ��̋���
//		KSdiff = m_Sposition - m_Knseiposition;
//		KTdiff = m_Tposition - m_Knseiposition;
//		KAdiff = m_aburaposition - m_Knseiposition;
//		//�����������炠���𓮂���
//		KaraageMove(m_Knseiposition, 8.0f);
//		//�����Ă邶�傤�����ő��̃V�[���s������߂��B
//		if (Pad(0).IsPress(enButtonB)) {
//			if (Pad(0).IsTrigger(enButtonRB1) ||
//				Pad(0).IsTrigger(enButtonLB1)) {
//				m_state = StateIdle;
//			}
//		}
//		//B�𗣂����A�g���O�Ƃ��炠�������ꂽ���A
//		if (!Pad(0).IsPress(enButtonB) ||
//			KTdiff.Length() >= 10.0f) {
//			//���Ƌ߂���Ή������Ȃ�
//			if (KAdiff.Length() <= 35.0f) {
//
//			}
//			//������Ώ����ʒu�ɖ߂��B
//			else {
//				OverS = 0.0f;
//				m_state = StateIdle;
//			}
//			//���M�Ƌ߂����
//			if (KSdiff.Length() <= 20.0f) {
//				//�������v���X�A�I�[�o�[�^�C����0�ɂ���
//				//StateIdle�Ɉړ�
//				KanseiKosuu++;
//				OverS = 0.0f;
//				m_state = StateIdle;
//
//			}
//		}
//		//�I�[�o�[�^�C�����w��ȏ�ɂȂ�����
//		//�����ɖ߂�
//		if (OverS >= 30.0f) {
//			OverS = 0.0f;
//			m_state = StateIdle;
//		}
//	}
//}

void SceneKaraage::Update()
{
	//���̃V�[�������炠���̏����Ȃ�A������
		//�J�[�\����ReturnMowScene�Ɏ����Ă�������ǂ̔ԍ����ǂ̃V�[�����킩��܂��B
	nowscene = m_camera->ReturnNowScene();
	if (nowscene == 0) {
		m_player->RgripAnimation();	//�v���C���[�͂����ƈ����Ă����B
		TongMove();					//�g���O�̓���
		//KaraageSyori();				//���炠���̏���
	}
	//L��R��������E����J��
	if (Pad(0).IsTrigger(enButtonRB1) ||
		Pad(0).IsTrigger(enButtonLB1)) {
		m_player->RopenAnimation();
	}
	if (Nowkarakosuu <= 0) {
		m_gene = NewGO<KaraageGenerator>(0, "karaagegenerator");
		Nowkarakosuu++;
	}
	//���炠����g����b���̃J�E���g
	/*if (m_state == Statefry) {
		KaraageS -= GameTime().GetFrameDeltaTime();
	}*/
	//�I�[�o�[�^�C���̃J�E���g
	/*if (m_state == Statekansei &&
		!Pad(0).IsPress(enButtonB)) {
		OverS += GameTime().GetFrameDeltaTime();
	}
	m_nama->SetPosition(m_Kposition);
	m_kansei->SetPosition(m_Knseiposition);*/

	//m_nama->SetEmissionColor({ 1.0f,1.0f,1.0f });
	/*CVector3 colar;
	colar.x = 0.0f;
	colar.y = 0.0f;
	colar.z = 0.0f;
	swprintf_s(text, L"%02d", KanseiKosuu);
	m_fontkansei->SetText(text);
	m_fontkansei->SetColor(colar);*/
}