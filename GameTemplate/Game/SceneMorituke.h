#pragma once
class Camera;
class Player;
class SceneMorituke : public IGameObject
{
public:
	SceneMorituke();
	~SceneMorituke();
	bool Start();
	void Move();
	void Cut();
	void Update();
	int ReturnKyabetuKansei()
	{
		return Kansei;
	}

private:
	Camera* m_camera = nullptr;
	Player* m_player = nullptr;

	prefab::CSkinModelRender* m_kyabetu = nullptr;		//�L���x�c
	prefab::CSkinModelRender* m_houtyou = nullptr;		//�
	prefab::CSkinModelRender* m_osara = nullptr;		//���M

	prefab::CSpriteRender* m_manaita = nullptr;			//�܂Ȕ�
	//prefab::CSpriteRender* m_cutkyabetu = nullptr;		//�؂����L���x�c
	prefab::CSpriteRender* m_cutOkyabetu = nullptr;		//���M�̃L���x�c

	CVector3 m_kyabetupos = { -3830.0f,0.0f,-20.0f };	//�L���x�c�̃|�W�V����
	CVector3 m_houtyoupos = { -3800.0f,0.0f,-20.0f };	//��̃|�W�V����
	CVector3 m_manaitapos = { -3840.0f,0.0f,-50.0f };	//�܂Ȕ̃|�W�V����
	//CVector3 m_cutkyabetupos = { -3854.0f,0.0f,-50.0f };	//�؂�ꂽ�L���x�c�̃|�W�V����
	CVector3 m_cutosarakyabetupos = { -3906.5f,4.0f,-10.0f };//���M�ɐ���ꂽ�L���x�c�̃|�W�V����

	CQuaternion m_houtyouRotation = CQuaternion::Identity;//��̉�]�B

	CQuaternion m_Srotation = CQuaternion::Identity;	//���M�̉�]�B
	CVector3 m_Kscal = CVector3::One;				//�L���x�c�̊g�嗦
	CVector3 m_Cutscal = { 0.0f, 0.04f, 0.03f };	//�؂����L���x�c�̊g�嗦
	CVector3 m_CutOsara = { 0.0f,0.0f,1.0f };	//{ 0.01f,0.01f,0.01f }���M�̃L���x�c�̊g�嗦
	CVector3 KMdiff = CVector3::Zero;				//�L���x�c�Ƃ܂Ȕ̋���
	CQuaternion Hanten;								//��]

	int nowscene = 0;	//���̃V�[��
	float CT = 30.0f;	//�J�b�g�̉�
	int Cutcount = 30;	//�A�ł����
	int Kansei = 0;		//�������B
};

