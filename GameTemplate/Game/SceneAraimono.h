#pragma once
class Player;
class Camera;
class SceneAraimono : public IGameObject
{
public:
	SceneAraimono();
	~SceneAraimono();
	bool Start();
	void Osara();
	void Update();
	int ReturnPoteto(){			//���������M�̐���Ԃ�
		return KanseiSara;
	}
private:

	enum State {
		State_Nothing,				//�������Ȃ����.
		State_wash,					//���M�����Ă����ԁB
		State_Generate,				//�V�������M�𐶐������ԁB
	};
	State m_state = State_Nothing;

	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	prefab::CSkinModelRender* m_osara = nullptr;			//���M�̃X�L�����f��
	CVector3 m_Oposition = CVector3::Zero;					//���M�̃|�W�V����
	CQuaternion m_Srotation = CQuaternion::Identity;		//���M�̉�]

	prefab::CSpriteRender* m_Yogore = nullptr;				//����X�L�����f��
	CVector3 m_YogoPos = { -5117.5f,-15.0f,-3.0f };			//����̃|�W�V����
	CVector3 Scale = { 0.010f, 0.015f, 0.01f };				//
	CQuaternion Hanten;										//��]

	CVector3 KPos = CVector3{ -5070.0f,0.0f,0.0f };			//�􂦂��M�̃|�W�V����	
	CVector3 ROdiff = CVector3::Zero;						//���M�ƉE��̋���
	float Araimo = 0.0f;									//����

	float KanseiSara = 0.0;									//�􂦂����M
	int Count = 0;											//���ԂƉ���k��������
	int Nowscene = 0;
};

