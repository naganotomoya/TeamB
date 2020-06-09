#pragma once
class Player;
class Camera;
class KaraageGenerator;
class SceneKaraage : public IGameObject
{
public:
	SceneKaraage();
	~SceneKaraage();
	bool Start();
	void TongMove();
	//void KaraageMove(CVector3& pos, float dif);
	//void KaraageSyori();
	void Update();

	//�g���O�̃|�W�V������Ԃ��B
	CVector3 ReturnTongPos()
	{
		return m_Tposition;
	}





	//�����Ă��邩�炠���̎��Ԃ�Ԃ�
	//�����͂P�T�b
	/*float ReturnKaraageJikan()
	{
		return KaraageS;
	}*/
	//�����������炠���̌���Ԃ��B
	int ReturnKaraageKansei()
	{
		return KanseiKosuu;
	}
	//���炠���������v���X
	void PlusKaraageKansei()
	{
		KanseiKosuu++;
	}
	//���炠�������}�C�i�X
	void MinusKaraageKansei()
	{
		KanseiKosuu--;
	}
	//�����݂��邩�炠�������}�C�i�X
	void minusNowkara()
	{
		Nowkarakosuu--;
	}

private:
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	KaraageGenerator* m_gene = nullptr;
	prefab::CSkinModelRender* m_tong = nullptr;		//�X�L�����f�������_���[�B
	//prefab::CSkinModelRender* m_nama = nullptr;		//�X�L�����f�������_���[�B
	prefab::CSkinModelRender* m_osara = nullptr;		//�X�L�����f�������_���[�B
	//prefab::CSkinModelRender* m_kansei = nullptr;		//�X�L�����f�������_���[�B


	CVector3 m_StartPos = CVector3::Zero;			//�����̃|�W�V�����B
	CVector3 m_Tposition = CVector3::Zero;			//�g���O�̃|�W�V�����B
	//CVector3 m_Kposition = CVector3::Zero;			//�����炠���̃|�W�V����
	////CVector3 m_Knseiposition = CVector3::Zero;			//�������炠���̃|�W�V����
	//CVector3 m_KnseiStartposition = { 0.0f,-100.0f,-5.0f };			//�������炠���̏����|�W�V����
	CVector3 m_Sposition = CVector3::Zero;			//���M�̃|�W�V����
	CQuaternion m_Trotation = CQuaternion::Identity;	//�g���O��]�B
	CQuaternion m_Srotation = CQuaternion::Identity;	//���M��]�B
	prefab::CSpriteRender* m_abura = nullptr;		//���̂QD
	CQuaternion Hanten;								//��]
	CVector3 m_aburaposition = CVector3::Zero;		//���̃|�W�V����
	//CVector3 KTdiff = CVector3::Zero;				//���炠���ƃg���O�̋���
	//CVector3 KSdiff = CVector3::Zero;				//���炠���Ƃ��M�̋���
	//CVector3 KAdiff = CVector3::Zero;				//���炠���Ɩ��̋���

	//float KaraageS = 10;		//���炠����a����b��
	int KanseiKosuu = 0;		//����������
	int nowscene = 0;	//���̃V�[�����ꂪ�Ȃ��Ƃ��ł��������Ⴄ
	//float OverS = 0;		//���炠����a����b��
	int Nowkarakosuu = 1;	//�����݂��邩�炠����

	/*enum State {
		StateIdle,
		Statepush,
		Statefry,
		Statekansei
	};
	State m_state = StateIdle;*/

	/*prefab::CFontRender* m_fontkansei = nullptr;
	wchar_t text[256];*/
};


