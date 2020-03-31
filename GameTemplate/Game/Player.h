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
	void Update();
	void PlusXPosition(float x)
	{
		m_Rposition.x += x;
		m_Lposition.x += x;
	}
	//B�������Ă���Ԏ��������ꍇ�̏���
	//if (Pad(0).IsPress(enButtonB)) {
	//	player->RgripAnimation();
	//}
	//else {
	//	player->RopenAnimation();
	//}
	//�E��̃A�j���[�V����(����)
	void RgripAnimation()
	{
		m_Rhand->PlayAnimation(rhandAC_grip);
	}
	//�E��̃A�j���[�V����(�J��)
	void RopenAnimation()
	{
		m_Rhand->PlayAnimation(rhandAC_open);
	}
	//�E���z����ݒ肷��B
	void setRHandZ(float posz)
	{
		m_Rposition.z = posz;
	}
	//�v���C���[��Y���Ɉ������̉�]��������
	void PlayerKaiten(float yjiku)
	{
		Yjiku.SetRotationDeg(CVector3::AxisY, yjiku);
		m_Rhand->SetRotation(Yjiku);
	}


	//�ړ�
	//�L�����ƈꏏ�Ɉړ����������Ƃ���
	//�����ɂ���position�����Ďg���B
	void Move(CVector3& pos);
	//�E��̈ʒu��Ԃ�
	CVector3 ReturnRPlayerPosition()
	{
		return m_Rposition;
	}
	//����𓮂���
	void SetLPosition(CVector3 pos)
	{
		m_Lposition = pos;
	}
	//����ʒu��Ԃ�
	CVector3 ReturnLPlayerPosition()
	{
		return m_Lposition;
	}
	//���肨�M�Ŏg���A�j���[�V����
	void LosaraAnime()
	{
		m_Lhand->PlayAnimation(lhandAC_osara);
	}
	void LosaraGrip()
	{
		m_Lhand->PlayAnimation(lhandAC_osaragrip);
	}

	//����̃A�j���[�V����
	void LgripAnimation()
	{
		m_Lhand->PlayAnimation(lhandAC_grip);
	}
	void LopenAnimation()
	{
		m_Lhand->PlayAnimation(lhandAC_open);
	}

private:
	Camera* m_camera = nullptr;
	enum LHandAC {
		lhandAC_open,
		lhandAC_grip,
		lhandAC_osara,
		lhandAC_osaragrip,
		lhandAC_Num,	//�A�j���[�V�����N���b�v�̐��B
	};
	enum RHandAC {
		rhandAC_open,
		rhandAC_grip,
		rhandAC_Num,	//�A�j���[�V�����N���b�v�̐��B
	};
	CAnimationClip m_Rac[rhandAC_Num];	//�A�j���[�V�����N���b�v�B
	CAnimationClip m_Lac[lhandAC_Num];	//�A�j���[�V�����N���b�v�B
	prefab::CSkinModelRender* m_Rhand = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_Lhand = nullptr;		//�X�L�����f�������_���[�B
	CVector3 m_Lposition = { 20.0f,-60.0f,0.0f };
	CVector3 m_Rposition = { 0.0f,0.0f,0.0f };
	CQuaternion Yjiku = CQuaternion::Identity;			//y������̉�]

	float movespeed = 1.0f;	//�ړ����x
	float CX = 1280.0f;	//�ړ����鋗��
	int scenenum = 0;	//�V�[���̐�
	int nowscene = 0;		//���̃V�[���ԍ�
	float tyuusin = 0.0f;
};