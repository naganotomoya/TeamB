#pragma once
#include "Player.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
class SceneDrink : public IGameObject
{
public:
	SceneDrink();
	~SceneDrink();
	bool Start();
	void Move();
	void Animation(CVector3& pos);
	void Update();
	void InitGhostObject();

	//�X�v���C�g�����_���[
	//prefab::CSkinModelRender* m_skinModelRenderer = nullptr;
	//�t�H���g�����_���[�B
	prefab::CFontRender* m_fontRender = nullptr;
	wchar_t text[256];
	CVector2 m_positiontekisuto = { 80.0f,200.0f };
	//CVector3 m_positiontekisuto = { -2580.0f,30.0f};

	//�ړ�
	CVector3 m_position = { -2480.0f,-15.0f,-6.0f };
	CVector3 m_position2 = { -2480.0f,-50.0f,-6.0f };

	CVector3 m_Startposition = { -2480.0f,-20.0f,-6.0f };
	CVector3 m_Startposition2 = { -2480.0f,-50.0f,-6.0f };

	CVector3 m_Pposition = CVector3::Zero;

	CVector3 m_positionG1 = { -2510.0f, -25.0f, -5.0f };
	CVector3 m_positionG2 = { -2553.0f, -25.0f, -5.0f };
	CVector3 m_positionG3 = { -2607.0f, -25.0f, -5.0f };
	CVector3 m_positionG4 = { -2645.0f, -20.0f, -5.0f };

	//�X�L�����f�������_���[
	prefab::CSkinModelRender* m_kop = nullptr;
	prefab::CSkinModelRender* m_kop2 = nullptr;
	prefab::CSkinModelRender* m_db = nullptr;


	//�ړ����x
	//CVector3 m_moveSpeed = CVector3::Zero;

	int m_state = 0;
	int dorinkucount = 0;

	bool kophave1 = false;
	bool kophave2 = false;
	bool Ghave1 = false;
	bool Ghave2 = false;


	Player* player = nullptr;
	//SceneDrink* koop1 = nullptr;

	enum EnAnimationClip {
		enAnimationClip_dorinkumizu, //�h�����N�A�j���[�V����
		enAnimationClip_kieru, //�h�����N�A�j���[�V����

		enAnimationClip_dorinkukoora,//�h�����N�A�j���[�V����
		enAnimationClip_kierukoora, //�h�����N�A�j���[�V����


		enAnimationClip_dorinkuotya,//�h�����N�A�j���[�V����
		enAnimationClip_kieruotya, //�h�����N�A�j���[�V����


		enAnimationClip_Num,	//�A�j���[�V�����N���b�v�̐��B

	};
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CAnimationClip m_animClips[enAnimationClip_Num];	//�A�j���[�V�����N���b�v�B

   //�S�[�X�g�I�u�W�F�N�g�Ƃ��S�B
	CPhysicsGhostObject m_ghostObject1;	//����
	CPhysicsGhostObject m_ghostObject2; //�R�[��
	CPhysicsGhostObject m_ghostObject3; //��
	CPhysicsGhostObject m_ghostObject4; //�����i

};