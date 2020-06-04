#pragma once
class Player;
class Camera;
class ScenePoteto : public IGameObject
{
public:
	ScenePoteto();
	~ScenePoteto();
	bool Start();
	void Update();
	float ReturnPotetoTime() {		//�|�e�g��g���Ă���b��
		return PoteFly;
	}
	int ReturnKanseiPoteto() {		//�|�e�g�����̕ϐ�
		return PotetoKansei;
	}
	void SetPotetoKosuu() {			//�|�e�g�̌����}�C�i�X
		PotetoKansei--;
	}
private:
	enum State{
		State_None,				//�������Ȃ����.
		State_PickPoteto,		//�|�e�g���^��ł����ԁB
		State_TranlateFlyer,	//�|�e�g�����M�ɐ���t�����ԁB
		State_oilinput,			//���̒��ɓ����Ă����ԁB
	};
	State m_state = State_None;
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	prefab::CSkinModelRender* m_Poteto = nullptr;		//���|�e�g�X�L�����f���B
	prefab::CSkinModelRender* m_KanseiPoteto = nullptr; //�|�e�g�X�L�����f���B
	prefab::CSkinModelRender* m_osara = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_Flyer = nullptr;		//�t���C���[�X�L�����f���B
	prefab::CSpriteRender* m_abura = nullptr;		//���̂QD


	
	
	CQuaternion Hanten;								//��]
	CVector3 m_aburaposition = CVector3::Zero;		//���̃|�W�V����

	CVector3 m_Fposition = CVector3::Zero;			//�t���C���[�|�W�V����
	CQuaternion FlyQuater;							//�t���C���[�̉�]�B
	
	CVector3 m_Pposition = CVector3::Zero;			//���|�e�̃|�W�V����
	CVector3 InitialPosition = { -1208.0f,0.0f,0.0f };//���|�e�����ʒu
	CVector3 m_Kanseiposition = { -1230.0f,0.0f,-300.0f };		//�����|�e�g�̃|�W�V����
	CVector3 m_Oposition = CVector3::Zero;			//���M�̃|�W�V����
	CQuaternion m_Srotation = CQuaternion::Identity;//���M�̉�]

	CVector3 PPdiff = CVector3::Zero;				//�|�e�g�ƃv���C���[�̎�̋���
	CVector3 PTdiff = CVector3::Zero;				//�|�e�g�ƎM�̋���
	CVector3 APdiff = CVector3::Zero;				//���ƃ|�e�g�̋���

	float PoteFly = 0.0;							//�|�e�g��g����b��
	int PotetoKansei = 0;							//���������|�e�g�̐�
	bool Nama = true;								//�������邩
	bool Fried = false;								//�g�����|�e�g�����邩
	int nowscene = 0;

};

