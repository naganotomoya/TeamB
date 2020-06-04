#include "stdafx.h"
#include "SceneDrink.h"
#include "Player.h"
#include "Camera.h"

SceneDrink::SceneDrink()
{
}
SceneDrink::~SceneDrink()
{
	DeleteGO(m_kop);
	DeleteGO(m_kop2);
	DeleteGO(m_db);
	DeleteGO(m_fontRender);
}
bool SceneDrink::Start()
{

	m_camera = FindGO<Camera>("camera");
	//�S�[�X�g�̏������B
	InitGhostObject();

	//���f�������[�h
	m_kop = NewGO<prefab::CSkinModelRender>(0, "koop1");
	m_kop->Init(L"modelData/koop1.cmo");
	m_kop->SetPosition(m_position);

	//���f�������[�h
	m_kop2 = NewGO<prefab::CSkinModelRender>(0, "koop2");
	m_kop2->Init(L"modelData/koop2.cmo");
	m_kop2->SetPosition(m_position2);
	m_kop2->SetScale({ 1.7f,1.7f,1.7f });

	//�A�j���[�V�����N���b�v�̃��[�h�B
	m_animClips[enAnimationClip_dorinkumizu].Load(L"animData/Drink/waterOut.tka");
	m_animClips[enAnimationClip_kieru].Load(L"animData/Drink/waterEnd2.tka");

	m_animClips[enAnimationClip_dorinkukoora].Load(L"animData/Drink/colaOut.tka");
	m_animClips[enAnimationClip_kierukoora].Load(L"animData/Drink/colaEnd.tka");

	m_animClips[enAnimationClip_dorinkuotya].Load(L"animData/Drink/chaOut.tka");
	m_animClips[enAnimationClip_kieruotya].Load(L"animData/Drink/chaEnd.tka");

	//���f�������[�h
	m_db = NewGO<prefab::CSkinModelRender>(0, "dorinkuba");
	m_db->Init(L"modelData/dorinkuba/dorinkuba.cmo", m_animClips, enAnimationClip_Num);
	m_db->SetPosition({ -2560.0f,-10.0f,-30.0f });
	m_db->SetScale({ 0.75f,0.75f,0.75f });




	//�����V���b�g�Đ��Œ�~����B
	m_animClips[enAnimationClip_dorinkumizu].SetLoopFlag(false);
	m_animClips[enAnimationClip_dorinkukoora].SetLoopFlag(false);
	m_animClips[enAnimationClip_dorinkuotya].SetLoopFlag(false);
	m_animClips[enAnimationClip_kieru].SetLoopFlag(false);
	m_animClips[enAnimationClip_kierukoora].SetLoopFlag(false);
	m_animClips[enAnimationClip_kieruotya].SetLoopFlag(false);


	m_fontRender = NewGO<prefab::CFontRender>(0);
	m_fontRender2 = NewGO<prefab::CFontRender>(0);
	m_fontRender2->SetColor(m_fontC);

	player = FindGO<Player>("player");
	return true;
}
void SceneDrink::Move()
{
	//�R�b�v1�̓����蔻��
	m_Pposition = player->ReturnRPlayerPosition();
	//�Q�_�Ԃ̋������v�Z����B
	CVector3 diff1 = m_Pposition - m_position;
	if (diff1.Length() <= 20.0f) {
		if (Pad(0).IsPress(enButtonB)
			&& kophave2 == false) {
			kophave1 = true;
			/*m_position.x = m_Pposition.x;
			m_position.y = m_Pposition.y;*/
			player->Move(m_position);
		}
	}
	//CVector3 diff = player->ReturnRPlayerPosition() - m_position;
	m_kop->SetPosition(m_position);

	//�R�b�v2�̓����蔻��
	//m_Pposition2 = player->ReturnRPlayerPosition();
	//�Q�_�Ԃ̋������v�Z����B
	CVector3 diff2 = m_Pposition - m_position2;
	if (diff2.Length() <= 20.0f) {
		if (Pad(0).IsPress(enButtonB)
			&& kophave1 == false) {
			kophave2 = true;
			/*m_position.x = m_Pposition.x;
			m_position.y = m_Pposition.y;*/

			player->Move(m_position2);
		}
	}
	//CVector3 diff = player->ReturnRPlayerPosition() - m_position;
	m_kop2->SetPosition(m_position2);
	if (!Pad(0).IsPress(enButtonB)
		&& kophave1 == true) {
		kophave1 = false;
	}
	if (!Pad(0).IsPress(enButtonB)
		&& kophave2 == true) {
		kophave2 = false;
	}

	//�Q�_�Ԃ̋������v�Z����B
	if (timer >= 5.0f) {
		CVector3 diff4 = m_positionG4 - m_position;
		CVector3 diff5 = m_positionG4 - m_position2;
		if (diff4.Length() <= 20.0f || diff5.Length() <= 20.0f) {
			if (!Pad(0).IsPress(enButtonB)) {
				dorinkucount++;
				m_state = Out;
			}
		}
	}


}


void SceneDrink::Animation(CVector3& pos)
{
	CVector3 diff1 = pos - m_positionG3;
	CVector3 diff2 = pos - m_positionG2;
	CVector3 diff3 = pos - m_positionG1;
	CVector3 diff4 = pos - m_positionG4;
//�ҋ@���
	if (m_state == Idle) {
		if (diff1.Length() <= 15.0f
			&& !Pad(0).IsPress(enButtonB)) {
			//�A�j���[�V�������Đ�
			//m_db->PlayAnimation(enAnimationClip_dorinkumizu);
			//���̃X�e�[�g�Ɉړ�
			m_state = Mizu;
		}
		if (diff2.Length() <= 15.0f
			&& !Pad(0).IsPress(enButtonB)) {
			//�A�j���[�V�������Đ�
			//m_db->PlayAnimation(enAnimationClip_dorinkukoora);
			//�R�[���̃X�e�[�g�Ɉړ�
			m_state = Cora;
		}
		if (diff3.Length() <= 15.0f
			&& !Pad(0).IsPress(enButtonB)) {
			//�A�j���[�V�������Đ�
			//m_db->PlayAnimation(enAnimationClip_dorinkuotya);
			//�����̃X�e�[�g�Ɉړ�
			m_state = Otya;
			
		}
	}
//���̃X�e�[�g
	if (m_state == Mizu) {
		//�{�b�N�X�Ƌ߂���΃A�j���[�V����
		if (diff1.Length() <= 15.0f
			&& !Pad(0).IsPress(enButtonB)) {
			//�A�j���[�V�������Đ�
			m_db->PlayAnimation(enAnimationClip_dorinkumizu);
			timer += GameTime().GetFrameDeltaTime();
			dorinkucountsuuzi -= GameTime().GetFrameDeltaTime();
			//5�b�Ŋ����iMove�j�ɋL�q
			if (timer >= 10.0f) {
				//10�b�ł��ӂ��
				m_state = Out;
			}
		}
	}
//�R�[���̃X�e�[�g
	if (m_state == Cora) {
		//�{�b�N�X�Ƌ߂���΃A�j���[�V����
		if (diff2.Length() <= 15.0f
			&& !Pad(0).IsPress(enButtonB)) {
			//�A�j���[�V�������Đ�
			m_db->PlayAnimation(enAnimationClip_dorinkukoora);
			timer += GameTime().GetFrameDeltaTime();
			dorinkucountsuuzi -= GameTime().GetFrameDeltaTime();
			//5�b�Ŋ����iMove�j�ɋL�q
			if (timer >= 10.0f) {
				//10�b�ł��ӂ��
				m_state = Out;
			}
		}	
	}
//�����̃X�e�[�g
	if (m_state == Otya) {
		//�{�b�N�X�Ƌ߂���΃A�j���[�V����
		if (diff3.Length() <= 15.0f
			&& !Pad(0).IsPress(enButtonB)) {
			//�A�j���[�V�������Đ�
			m_db->PlayAnimation(enAnimationClip_dorinkuotya);
			timer += GameTime().GetFrameDeltaTime();
			dorinkucountsuuzi -= GameTime().GetFrameDeltaTime();
			//5�b�Ŋ����iMove�j�ɋL�q
			if (timer >= 10.0f) {
				//10�b�ł��ӂ��
				m_state = Out;
			}
		}
	}
//��ꂽ���A�������Č��̈ʒu�ɃR�b�v���߂���
	if (m_state == Out) {
		m_position = m_Startposition;
		m_position2 = m_Startposition2;
		m_db->PlayAnimation(enAnimationClip_kieru);
		timer = 5.0f;
		dorinkucountsuuzi = 5.0f;
		m_state = Idle;
	}

	//����
	if (Pad(0).IsTrigger(enButtonRB1) ||
		Pad(0).IsPress(enButtonLB1) ||
		Pad(0).IsPress(enButtonB)) {
		m_db->PlayAnimation(enAnimationClip_kieru);
	}

}

void SceneDrink::Update()
{
	Move();
	Animation(m_position);
	Animation(m_position2);



	//timer += GameTime().GetFrameDeltaTime();

	swprintf_s(text, L"�����i%d��", dorinkucount);
	m_fontRender->SetText(text);
	m_fontRender->SetPosition(m_positiontekisuto);


	//int minute = (int)dorinkucountsuuzi / 60;
	if (m_camera->ReturnNowScene() != 2) {
		m_fontC.w = 0.0f;
		m_fontRender2->SetColor(m_fontC);
	}
	if (m_camera->ReturnNowScene() == 2) {
		m_fontC.w = 1.0f;
		m_fontRender2->SetColor(m_fontC);
	}
	float sec = (int)dorinkucountsuuzi % 60;
	swprintf_s(text2, L"�����܂�%02.0f",sec);
	m_fontRender2->SetText(text2);
	m_fontRender2->SetPosition(m_positiontekisuto2);
	m_fontRender2->SetColor(m_fontC);


	//A�{�^���������ꂽ��ҋ@���[�V�������Đ�����B
	/*if (Pad(0).IsPress(enButtonA)) {
		m_db->PlayAnimation(enAnimationClip_kieru);
	}*/

	/*if (m_kop) {

		m_position = m_Startposition;
	}*/
	//m_position = m_Startposition;
}

void SceneDrink::InitGhostObject()
{
	//�S�[�X�g�̃��C���[�t���[���\����L���ɂ���B
	//PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	//����
	m_ghostObject1.CreateBox(
		m_positionG1,	//�������͍��W�B
		CQuaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
		{ 20.0f, 20.0f, 15.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);

	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	//�R�[��
	m_ghostObject2.CreateBox(
		m_positionG2,	//�������͍��W�B
		CQuaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
		{ 23.0f, 20.0f, 15.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);
	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	//��
	m_ghostObject3.CreateBox(
		m_positionG3,	//�������͍��W�B
		CQuaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
		{ 20.0f, 20.0f, 15.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);

	//�{�b�N�X�`��̃S�[�X�g���쐬����B
	//�����i
	m_ghostObject4.CreateBox(
		m_positionG4,	//�������͍��W�B
		CQuaternion::Identity,		//�������͉�]�N�H�[�^�j�I���B
		{ 30.0f, 100.0f, 10.0f }	//��O�����̓{�b�N�X�̃T�C�Y�B
	);


}