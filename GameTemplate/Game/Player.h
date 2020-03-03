#pragma once
class Camera;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void SetXPosition(float x);
	void Animation();
	void Move();
	void Update();
	void PlusXPosition(float x)
	{
		m_Rposition.x += x;
		m_Lposition.x += x;
	}

	//�E��̈ʒu��Ԃ�
	CVector3 ReturnRPlayerPosition()
	{
		return m_Lposition;
	}
	//�����Ȃ����𓮂���
	void SetLPosition(CVector3 pos)
	{
		m_Lposition = pos;
	}
	//�����Ȃ����̈ʒu��Ԃ�
	CVector3 ReturnLPlayerPosition()
	{
		return m_Rposition;
	}
	//����̃A�j���[�V����
	void LgripAnimation()
	{
		m_Rhand->PlayAnimation(rhandAC_grip);
	}
	void LopenAnimation()
	{
		m_Rhand->PlayAnimation(rhandAC_open);
	}

private:
	Camera* m_camera = nullptr;
	enum RHandAC {
		rhandAC_open,
		rhandAC_grip,
		rhandAC_Num,	//�A�j���[�V�����N���b�v�̐��B
	};
	enum LHandAC {
		lhandAC_open,
		lhandAC_grip,
		lhandAC_Num,	//�A�j���[�V�����N���b�v�̐��B
	};
	CAnimationClip m_Rac[rhandAC_Num];	//�A�j���[�V�����N���b�v�B
	CAnimationClip m_Lac[lhandAC_Num];	//�A�j���[�V�����N���b�v�B
	prefab::CSkinModelRender* m_Rhand = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_Lhand = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_Rposition = { 20.0f,-60.0f,0.0f };
	CVector3 m_Lposition = { 0.0f,0.0f,0.0f };

	float movespeed = 1.0f;	//�ړ����x
	float CX = 1280.0f;	//�ړ����鋗��
	int scenenum = 0;	//�V�[���̐�
	int nowscene = 0;		//���̃V�[���ԍ�
	float tyuusin = 0.0f;
};
