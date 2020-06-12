#pragma once
class SceneKaraage;
class Player;
class Camera;
class KaraageGenerator : public IGameObject
{
public:
	KaraageGenerator();
	~KaraageGenerator();
	bool Start();
	//void TongMove();
	void KaraageMove(CVector3& pos, float dif);
	void KaraageSyori();
	void Update();

	//�����Ă��邩�炠���̎��Ԃ�Ԃ�
	//�����͂P�T�b
	float ReturnKaraageJikan()
	{
		return KaraageS;
	}
	/*bool KaraageState()
	{
		return nextKara;
	}*/
	////�����������炠���̌���Ԃ��B
	//int ReturnKaraageKansei()
	//{
	//	return KanseiKosuu;
	//}
	//void MinusKaraageKansei()
	//{
	//	KanseiKosuu--;
	//}

private:
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	SceneKaraage* m_karaage = nullptr;
	//prefab::CSkinModelRender* m_tong = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_nama = nullptr;		//�X�L�����f�������_���[�B
	//prefab::CSkinModelRender* m_osara = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_kansei = nullptr;		//�X�L�����f�������_���[�B

	CVector3 ZeroScale = CVector3::Zero;			//�S�ĂO
	CVector3 m_StartPos = CVector3::Zero;			//�����̃|�W�V�����B
	CVector3 m_Tongposition = CVector3::Zero;			//�g���O�̃|�W�V�����B
	CVector3 m_Kposition = CVector3::Zero;			//�����炠���̃|�W�V����
	CVector3 m_Knseiposition = CVector3::Zero;			//�������炠���̃|�W�V����
	CVector3 m_KnseiStartposition = { 0.0f,-100.0f,-5.0f };			//�������炠���̏����|�W�V����
	//CVector3 m_Sposition = CVector3::Zero;			//���M�̃|�W�V����
	CVector3 m_Sposition = { -60.0f,0.0f,-10.0f };
	//CQuaternion m_Trotation = CQuaternion::Identity;	//�g���O��]�B
	//CQuaternion m_Srotation = CQuaternion::Identity;	//���M��]�B
	//prefab::CSpriteRender* m_abura = nullptr;		//���̂QD
	CQuaternion Hanten;								//��]
	//CVector3 m_aburaposition = CVector3::Zero;		//���̃|�W�V����
	CVector3 m_aburaposition = { -8.5f,0.0f,-2.5f };
	CVector3 KTdiff = CVector3::Zero;				//���炠���ƃg���O�̋���
	CVector3 KSdiff = CVector3::Zero;				//���炠���Ƃ��M�̋���
	CVector3 KAdiff = CVector3::Zero;				//���炠���Ɩ��̋���

	prefab::CSpriteRender* waku = nullptr;
	prefab::CSpriteRender* baa = nullptr;
	CVector3 SScale = { 0.008f,0.008f,1.0f };
	//CVector3 baapos = CVector3::Zero;
	CVector3 baaScale = { 0.0f,0.008f,1.0f };
	CVector3 baapos = CVector3::Zero;
	CVector3 wakupos = CVector3::Zero;

	CVector4 baacolor = { 0.0f,0.5f,0.0f,1.0f };

	float KaraageS = 0;		//���炠����a����b��
	//int KanseiKosuu = 0;		//����������
	int nowscene = 0;	//���̃V�[�����ꂪ�Ȃ��Ƃ��ł��������Ⴄ
	float OverS = 20;		//���炠����a����b��
	//bool nextKara = false;

	enum State {
		StateIdle,
		Statepush,
		Statefry,
		Statekansei
	};
	State m_state = StateIdle;

	prefab::CSoundSource* m_age = nullptr;
};

