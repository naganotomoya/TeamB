#pragma once
class Player;
class SceneAraimono : public IGameObject
{
public:
	SceneAraimono();
	~SceneAraimono();
	bool Start();
	void Update();
private:
	Player* m_player = nullptr;
	prefab::CSkinModelRender* m_osara = nullptr;//���M�̃X�L�����f��
	CVector3 m_Oposition = CVector3::Zero;			//���M�̃|�W�V����
	CQuaternion m_Srotation = CQuaternion::Identity;//���M�̉�]

};

