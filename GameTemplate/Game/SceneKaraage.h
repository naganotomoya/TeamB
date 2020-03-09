#pragma once
class Player;
class Camera;
class SceneKaraage : public IGameObject
{
public:
	SceneKaraage();
	~SceneKaraage();
	bool Start();
	void TongMove();
	void KaraageMove(CVector3& pos);
	void KaraageSyori();
	void FrySyori();
	void Update();

	//�����Ă��邩�炠���̎��Ԃ�Ԃ�
	float ReturnKaraageJikan()
	{
		return KaraageS;
	}
	//�����������炠���̌���Ԃ��B
	int ReturnKaraageKansei()
	{
		return KanseiKosuu;
	}

private:
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	prefab::CSkinModelRender* m_tong = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_nama = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_osara = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_kansei = nullptr;		//�X�L�����f�������_���[�B


	CVector3 m_StartPos = CVector3::Zero;			//�����̃|�W�V�����B
	CVector3 m_Tposition = CVector3::Zero;			//�g���O�̃|�W�V�����B
	CVector3 m_Kposition = CVector3::Zero;			//�����炠���̃|�W�V����
	CVector3 m_Knseiposition = CVector3::Zero;			//�������炠���̃|�W�V����
	CVector3 m_Sposition = CVector3::Zero;			//���M�̃|�W�V����
	CQuaternion m_Trotation = CQuaternion::Identity;	//�g���O��]�B
	CQuaternion m_Srotation = CQuaternion::Identity;	//����������]�B
	prefab::CSpriteRender* m_abura = nullptr;		//���̂QD
	CQuaternion Hanten;								//��]
	CVector3 m_aburaposition = CVector3::Zero;		//���̃|�W�V����
	CVector3 KTdiff = CVector3::Zero;				//���炠���ƃg���O�̋���
	CVector3 KSdiff = CVector3::Zero;				//���炠���Ƃ��M�̋���
	CVector3 KAdiff = CVector3::Zero;				//���炠���Ɩ��̋���

	float KaraageS = 0;		//���炠����a����b��
	bool pushkara = false;		//���炠������������
	bool fry = false;			//���炠���������Ă��邩
	bool kansei = false;		//�����������炠�������邩

	int KanseiKosuu = 0;		//����������
	int nowscene = 0;	//���̃V�[�����ꂪ�Ȃ��Ƃ��ł��������Ⴄ


	//prefab::CFontRender* m_fontkansei = nullptr;
	//wchar_t text[256];
};


