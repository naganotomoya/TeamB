#include "stdafx.h"
#include "KaraageGenerator.h"
#include "SceneKaraage.h"
#include "Player.h"
#include "Camera.h"

KaraageGenerator::KaraageGenerator()
{
}

KaraageGenerator::~KaraageGenerator()
{
	//DeleteGO(m_tong);
	DeleteGO(m_nama);
	//DeleteGO(m_abura);
	//DeleteGO(m_osara);
	DeleteGO(m_kansei);
	DeleteGO(baa);
	DeleteGO(waku);
	DeleteGO(m_age);

}

bool KaraageGenerator::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	m_karaage = FindGO<SceneKaraage>("karaage");
	//�g���O
	//m_tong = NewGO<prefab::CSkinModelRender>(0, "tong");
	//m_tong->Init(L"modelData/tongs.cmo");
	////���f�����������牺�̂͑�������Ȃ��B
	//m_Trotation.SetRotationDeg(CVector3::AxisX, 180.0f);
	//m_tong->SetRotation(m_Trotation);
	//m_tong->SetScale({ 2.0f,2.0f,2.0f });
	////���̂��炠��
	m_nama = NewGO<prefab::CSkinModelRender>(0);
	//m_nama->Init(L"modelData/KaraageS/Nama.cmo");
	m_nama->Init(L"modelData/KaraageS/kara/namakara.cmo");
	m_Kposition = { 74.0f,0.0f,-5.0f };
	m_StartPos = m_Kposition;
	m_nama->SetPosition(m_Kposition);
	//���M
	/*m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_osara->SetRotation(m_Srotation);
	m_Sposition = { -60.0f,0.0f,-10.0f };
	m_osara->SetPosition(m_Sposition);*/

	//��
	//2D�\������Ƃ����̂܂܂��ƂłȂ��Ǝv������3D�\���ɂ��Ĕ��]�����Ă��������B
	//m_abura = NewGO<prefab::CSpriteRender>(0);
	//m_abura->Init(
	//	L"sprite/Phaikei/Abura.dds",
	//	MainCamera().GetWidth(),
	//	MainCamera().GetHeight(),
	//	true	//3D�\��
	//);
	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//���]
	//m_abura->SetScale({ 0.04f,0.08f,0.05f });
	//m_aburaposition = { -8.5f,0.0f,-2.5f };
	//m_abura->SetPosition(m_aburaposition);
	//m_abura->SetRotation(Hanten);					//���]��K��
	//m_abura->SetMulColor({ 1.0f,1.0f,1.0f,0.8f });
	////�����������炠��
	m_kansei = NewGO<prefab::CSkinModelRender>(0);
	//m_kansei->Init(L"modelData/KaraageS/Kansei.cmo");
	m_Knseiposition = m_KnseiStartposition;
	m_kansei->SetPosition(m_Knseiposition);

	//m_fontkansei = NewGO<prefab::CFontRender>(0);
	waku = NewGO<prefab::CSpriteRender>(0);
	baa = NewGO<prefab::CSpriteRender>(0);
	baa->SetPivot({ 0.0f,0.5f });
	/*baa->Init(L"sprite/Hiyoko/ba-.dds", 250.0f, 250.0f);
	baa->SetPivot(piv);
	baa->SetPosition({ -635.0f,230.0f,0.0f });*/

	m_age = NewGO<prefab::CSoundSource>(0);
	m_age->Init(L"sound/SE/age.wav");
	m_age->SetVolume(0.0f);

	return true;
}

//void KaraageGenerator::TongMove()
//{
//	//�v���C���[�̃|�W�V�������g����
//	//�g���O�̃|�W�V�����ɂ���
//	m_Tposition = m_player->ReturnRPlayerPosition();
//	m_Tposition.x += 2.0f;
//	m_Tposition.y += 25.0f;
//	m_Tposition.z += -3.0f;
//	m_tong->SetPosition(m_Tposition);
//}

void KaraageGenerator::KaraageMove(CVector3& pos, float dif)
{
	KTdiff = m_Tongposition - pos;
	//���炠���ƃg���O�̋������߂��āA
	//B�{�^����������Ă���Ƃ��B
	//�A�j���[�V�����ǉ��������ɂ��̏������ǉ�
	//�A�j���[�V�������Đ�����Ă��鎞�Ƃ��������ǉ�������
	//����Ƃ��������߂Ȃ��悤�ɏo����͂��B
	if (KTdiff.Length() <= dif &&
		Pad(0).IsPress(enButtonB)) {
		//m_player->Move()�̓v���C���[�N���X�ɒ�`�錾
		//�v���C���[�Ɠ�������������B
		//�����ɍD���ȕϐ�����ꂽ��ǂ��ł��g����B
		m_player->Move(pos);
	}
}

void KaraageGenerator::KaraageSyori()
{
	/*�����ʒu�A�ҋ@*/
	if (m_state == StateIdle) {
		//������Ɗ����������炠���������|�W�ɖ߂��B
		m_Kposition = m_StartPos;
		//m_Knseiposition = m_KnseiStartposition;
		//���炠���g���O�̋���
		KTdiff = m_Tongposition - m_Kposition;
		//���炠���ƃg���O���߂��āAB��������Ă���ƁA
		//Statepush�Ɉړ�
		if (KTdiff.Length() <= 8.0f &&
			Pad(0).IsPress(enButtonB)) {
			m_state = Statepush;
		}
	}
	/*�����玝�������*/
	if (m_state == Statepush) {
		//�����炠���𓮂����B
		KaraageMove(m_Kposition, 8.0f);
		//�V�[����ς�����A�����ʒu��
		if (Pad(0).IsTrigger(enButtonRB1) ||
			Pad(0).IsTrigger(enButtonLB1)) {
			//m_state = StateIdle;
			m_karaage->minusNowkara();
			DeleteGO(this);
		}
		//B�𗣂������A���Ƌ߂���Ύ��̏���
		if (!Pad(0).IsPress(enButtonB) ||
			KTdiff.Length() >= 10.0f) {
			//���炠���Ɩ��̋���
			KAdiff = m_aburaposition - m_Kposition;
			if (KAdiff.Length() <= 35.0f) {
				wakupos = m_Kposition;
				wakupos.z += 3.0f;
				baapos = m_Kposition;
				baapos.z += 3.0f;
				baapos.x += 5.0f;
				baa->Init(
					L"sprite/Karaage/baa.dds",
					MainCamera().GetWidth(),
					MainCamera().GetHeight(),
					true);
				baa->SetRotation(Hanten);
				baa->SetScale(SScale);
				baa->SetPosition(baapos);
				waku->Init(
					L"sprite/Karaage/baawaku.dds",
					MainCamera().GetWidth(),
					MainCamera().GetHeight(),
					true);
				waku->SetRotation(Hanten);
				waku->SetScale(SScale);
				waku->SetPosition(wakupos);
				m_karaage->minusNowkara();
				m_state = Statefry;
			}
			//������Ώ����ʒu�֖߂��B
			else {
				//m_state = StateIdle;
				m_karaage->minusNowkara();
				DeleteGO(this);
			}
		}
	}
	/*�g������*/
	if (m_state == Statefry) {
		baaScale.x = KaraageS * 0.0008f;
		baa->SetScale(baaScale);

		m_age->Play(true);
		m_age->SetVolume(1.0f);

		//�w�肵���b���o������
		if (KaraageS >= 10.0f) {
			//�����������炠�����o��
			//m_kansei->Init(L"modelData/KaraageS/Kansei.cmo");
			m_kansei->Init(L"modelData/KaraageS/kara/Age.cmo");
			m_Knseiposition = m_Kposition;
			//m_Kposition = m_StartPos;
			m_nama->SetScale(ZeroScale);
			//�����邩�炠���̌��̕ύX
			//m_karaage->minusNowkara();
			//�b���������ɖ߂��āAStatekansei�Ɉړ�
			KaraageS = 0.0f;
			m_state = Statekansei;
		}
	}
	/*�����������炠����������*/
	if (m_state == Statekansei) {

		if (KAdiff.Length() <= 35.0f) {
			m_age->SetVolume(0.5f);
		}
		else {
			m_age->SetVolume(0.0f);
		}

		baa->SetMulColor(baacolor);
		baaScale.x = (OverS / 2) * 0.0008f;
		baa->SetScale(baaScale);
		wakupos = m_Knseiposition;
		wakupos.z += 3.0f;
		baapos = m_Knseiposition;
		baapos.z += 3.0f;
		baapos.x += 5.0f;
		baa->SetPosition(baapos);
		waku->SetPosition(wakupos);
		//���ꂼ��̋���
		KSdiff = m_Sposition - m_Knseiposition;
		KTdiff = m_Tongposition - m_Knseiposition;
		KAdiff = m_aburaposition - m_Knseiposition;
		//�����������炠���𓮂���
		KaraageMove(m_Knseiposition, 8.0f);
		//�����Ă邶�傤�����ő��̃V�[���s������߂��B
		if (Pad(0).IsPress(enButtonB)) {
			if (Pad(0).IsTrigger(enButtonRB1) ||
				Pad(0).IsTrigger(enButtonLB1)) {
				//m_state = StateIdle;
				DeleteGO(this);
			}
		}
		//B�𗣂����A�g���O�Ƃ��炠�������ꂽ���A
		if (!Pad(0).IsPress(enButtonB) ||
			KTdiff.Length() >= 10.0f) {
			//���Ƌ߂���Ή������Ȃ�
			if (KAdiff.Length() <= 35.0f) {

			}
			else {
				//���M�Ƌ߂����
				if (KSdiff.Length() <= 20.0f) {
					prefab::CSoundSource* pikon;
					pikon = NewGO<prefab::CSoundSource>(0);
					pikon->Init(L"sound/SE/pikon.wav");
					pikon->Play(false);

					//�������v���X�A�I�[�o�[�^�C����0�ɂ���
					//StateIdle�Ɉړ�
					//KanseiKosuu++;
					m_karaage->PlusKaraageKansei();
					OverS = 0.0f;
					//m_state = StateIdle;
					DeleteGO(this);

				}//������Ώ����ʒu�ɖ߂��B
				else {
					prefab::CSoundSource* bubu;
					bubu = NewGO<prefab::CSoundSource>(0);
					bubu->Init(L"sound/SE/cancel.wav");
					bubu->Play(false);

					OverS = 0.0f;
					//m_state = StateIdle;
					DeleteGO(this);
				}
			}
		}
		//�I�[�o�[�^�C�����w��ȏ�ɂȂ�����
		//�����ɖ߂�
		if (OverS <= 0.0f) {
			OverS = 20.0f;
			//m_state = StateIdle;
			DeleteGO(this);
		}
	}
}

void KaraageGenerator::Update()
{
	KaraageSyori();				//���炠���̏���
	//���̃V�[�������炠���̏����Ȃ�A������
		//�J�[�\����ReturnMowScene�Ɏ����Ă�������ǂ̔ԍ����ǂ̃V�[�����킩��܂��B
	nowscene = m_camera->ReturnNowScene();
	if (nowscene == 0) {
		m_Tongposition = m_karaage->ReturnTongPos();
		//m_player->RgripAnimation();	//�v���C���[�͂����ƈ����Ă����B
		//TongMove();					//�g���O�̓���
		//KaraageSyori();				//���炠���̏���
	}
	else {
		m_age->SetVolume(0.0f);
	}
	//L��R��������E����J��
	/*if (Pad(0).IsTrigger(enButtonRB1) ||
		Pad(0).IsTrigger(enButtonLB1)) {
		m_player->RopenAnimation();
	}*/
	//���炠����g����b���̃J�E���g
	if (m_state == Statefry) {
		KaraageS += GameTime().GetFrameDeltaTime();
	}
	//�I�[�o�[�^�C���̃J�E���g
	if (m_state == Statekansei /*&&
		!Pad(0).IsPress(enButtonB)*/) {
		OverS -= GameTime().GetFrameDeltaTime();
		//karaclo = (19-OverS) / 20.0f;
	}
	m_nama->SetPosition(m_Kposition);
	m_kansei->SetPosition(m_Knseiposition);

	//m_kansei->SetEmissionColor({ 0.0f, 0.0f, karaclo });
	//m_nama->SetEmissionColor({ 1.0f,1.0f,1.0f });
	/*CVector3 colar;
	colar.x = 0.0f;
	colar.y = 0.0f;
	colar.z = 0.0f;
	swprintf_s(text, L"%02d", KanseiKosuu);
	m_fontkansei->SetText(text);
	m_fontkansei->SetColor(colar);*/
}