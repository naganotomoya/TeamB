#pragma once
class ScenePoteto : public IGameObject
{
public:
	ScenePoteto();
	~ScenePoteto();
	bool Start();
	void Update();
private:
	prefab::CSkinModelRender* m_Poteto = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_osara = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSpriteRender* m_abura = nullptr;		//���̂QD
	CQuaternion Hanten;								//��]
	CVector3 m_aburaposition = CVector3::Zero;		//���̃|�W�V����
	CVector3 m_Pposition = CVector3::Zero;			//���|�e�̃|�W�V����
};

