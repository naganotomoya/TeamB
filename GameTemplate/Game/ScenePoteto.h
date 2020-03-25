#pragma once
class Player;
class Camera;
class ScenePoteto : public IGameObject
{
public:
	ScenePoteto();
	~ScenePoteto();
	bool Start();
	void PotetoMove(CVector3& pos);
	void Update();
private:
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	prefab::CSkinModelRender* m_Poteto = nullptr;		//�|�e�g�X�L�����f���B
	prefab::CSkinModelRender* m_osara = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_Flyer = nullptr;		//�t���C���[�X�L�����f���B
	prefab::CSpriteRender* m_abura = nullptr;		//���̂QD


	

	CQuaternion Hanten;								//��]
	CVector3 m_aburaposition = CVector3::Zero;		//���̃|�W�V����

	CVector3 m_Fposition = CVector3::Zero;			//�t���C���[�|�W�V����
	CQuaternion FlyQuater;							//�t���C��[�̉�]�B
	CVector3 m_Pposition = CVector3::Zero;			//���|�e�̃|�W�V����
	CVector3 m_Oposition = CVector3::Zero;			//���M�̃|�W�V����
	CQuaternion m_Srotation = CQuaternion::Identity;//���M�̉�]
	CVector3 PPdiff = CVector3::Zero;				//�|�e�g�ƃv���C���[�̎�̋���

	bool pushPote = false;		//�|�e�g����������
};

