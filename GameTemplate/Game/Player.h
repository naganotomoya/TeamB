#pragma once
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();

private:
	enum RHandAC {
		rhandAC_open,
		rhandAC_grip,
		rhandAC_Num,	//�A�j���[�V�����N���b�v�̐��B
	};
	//enum LHandAC {
	//	lhandAC_open,
	//	lhandAC_grip,
	//	lhandAC_Num,	//�A�j���[�V�����N���b�v�̐��B
	//};

	CAnimationClip m_Rac[rhandAC_Num];	//�A�j���[�V�����N���b�v�B
	//CAnimationClip m_Lac[lhandAC_Num];	//�A�j���[�V�����N���b�v�B

	prefab::CSkinModelRender* m_Rhand = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_Lhand = nullptr;		//�X�L�����f�������_���[�B

};

