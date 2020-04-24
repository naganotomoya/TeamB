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
private:
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	prefab::CSkinModelRender* m_osara = nullptr;			//���M�̃X�L�����f��
	CVector3 m_Oposition = CVector3::Zero;					//���M�̃|�W�V����
	CQuaternion m_Srotation = CQuaternion::Identity;		//���M�̉�]

	prefab::CSpriteRender* m_Yogore = nullptr;				//����X�L�����f��
	CVector3 m_YogoPos = { -5110.0f,0.0f,0.0f };			//����̃|�W�V����

	CVector3 KPos = CVector3{ -5070.0f,0.0f,0.0f };			//�􂦂��M�̃|�W�V����	
	CVector3 ROdiff = CVector3::Zero;						//���M�ƉE��̋���
	float Araimo = 0.0f;										//����

	float KanseiSara = 0.0;									//�􂦂����M
	int Nowscene = 0;
};

