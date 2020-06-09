#pragma once
class SceneKaikei;
class SceneKaraage;
class ScenePoteto;
class SceneMorituke;
class SceneDrink;
class SceneAraimono;
class SpriteGenerator : public IGameObject
{
public:
	SpriteGenerator();
	~SpriteGenerator();
	bool Start();

	void SetPosX();//�������Ƒҋ@���̏ꏊ�����߂�
	void SpriteState();//���ʂ̃X�e�[�g����
	void KaikeiSyori();//�X�e�[�g�ύX�̉�v���̂݁B�������番�����B
	void NokoriBaa();//�o�[�̏���
	void ColorFade();//���̏����ɍs���O�̃t�F�C�h
	void SetKosuu();//���ꂼ��̊����������߂�B

	//���ꂼ��̃`�F�b�N�}�[�N�̏����B�����ƊȒP�ȏ����Ƃ��V�����B
	void CHKara();
	void CHPote();
	void CHYasai();
	//1�͐��A2�̓R�[���A3�͂���
	void CHDrink(int num);


	void Update();

private:

	SceneKaraage* m_karaage = nullptr;
	ScenePoteto* m_poteto = nullptr;
	SceneMorituke* m_morituke = nullptr;
	SceneDrink* m_drink = nullptr;
	SceneAraimono* m_araimono = nullptr;
	SceneKaikei* m_kaikei = nullptr;

	prefab::CSpriteRender* m_sprite = nullptr;
	//prefab::CSpriteRender* waku = nullptr;
	prefab::CSpriteRender* baa = nullptr;
	prefab::CSpriteRender* CheckK = nullptr;
	prefab::CSpriteRender* CheckP = nullptr;
	prefab::CSpriteRender* CheckY = nullptr;
	prefab::CSpriteRender* CheckD = nullptr;

	float PosX = 0.0f;

	CVector3 nextScale = { 0.5f,0.5f,0.5f };

	CVector3 StartPos = { -510.0f,230.0f,0.0f };

	CVector4 Fade = { 1.0f,1.0f,1.0f,1.0f };
	bool fade = false;
	int fadeCount = 0;

	CVector3 BaaScale = { 1.0f,1.0f,1.0f };
	float timer = 40.0f;

	bool start = false;
	int setscene = 0;
	int scene = 0;
	int setstate = 0;
	enum State {
		Girl,
		Boy,
		Oldman,
		Fat,
		Kaikei,
		Idle,
		GKaikei,
		BKaikei,
		OKaikei,
		FKaikei,
		NextKaikei,
		DeleteThis
	};
	State m_state = Idle;

	int num = 1;

	int Kara = 0;
	int Pote = num;
	int Yasai = 0;
	int mizu = num;
	int kora = num;
	int otya = num;

	//���������ƊȒP�ɏ����邾�낤���ǁA�V����
	bool SetKara = false;
	bool SetPote = false;
	bool SetYasai = false;
	bool SetDrink = false;
	/*struct Tyuumon
	{
		bool Kara = true;
		bool Pote = true;
		bool Yasai = true;
		bool mizu = false;
		bool kora = false;
		bool otya = false;
	};
	Tyuumon tyuumon[Kaikei];*/

	CVector2 piv = { 0.0f,0.5f };

};

