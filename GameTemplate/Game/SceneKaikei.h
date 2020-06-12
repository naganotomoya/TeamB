#pragma once
class SpriteGenerator;
class SceneKaraage;
class ScenePoteto;
class SceneMorituke;
class SceneDrink;
class SceneAraimono;
class SceneKaikei : public IGameObject
{
public:
	SceneKaikei();
	~SceneKaikei();
	int NowKyaku()
	{
		return ninzuu;
	}
	//���q����̔ԍ�
	int KyakuNum()
	{
		return kyakunum;
	}
	//���q����ԍ��̕ύX
	void SetKyakuNum();
	void NextTyuumon();
	//���q��������炷�B
	void Setninzuu()
	{
		ninzuu--;
	}
	//���̏������̂��q����
	int NowTyuumon()
	{
		return Nowscene;
	}
	//�����_���Ō��肵�����q����
	int RandamuKyaku()
	{
		return Rokyaku;
	}
	//���ʂ�+�P
	void KanseiKo()
	{
		KanseiKekka++;
	}
	//���ʂ�Ԃ�
	int ReturnKekka()
	{
		return KanseiKekka;
	}
	bool ReturnYogore()
	{
		return Yogore;
	}
	bool Start();
	void Update();
	void YogoreSyori();

private:
	SpriteGenerator* m_spriteGene = nullptr;

	prefab::CSpriteRender* m_spriteYogore = nullptr;

	SceneKaraage* m_karaage = nullptr;
	ScenePoteto* m_poteto = nullptr;
	SceneMorituke* m_morituke = nullptr;
	SceneDrink* m_drink = nullptr;
	SceneAraimono* m_araimono = nullptr;

	/*struct Tyuumon
	{
		bool Karaage;
		bool Poteto;
		bool Drink;
		bool Morituke;
	};
	enum
	{
		kyaku1,
		kyaku2,
		kyakunum
	};

	Tyuumon Kaikei[kyakunum];*/
	//���̒�������������܂ł̕b��
	float timer = 10.0f;
	//����p�^�C�}�[
	float Yogoretimer = 0.0f;
	//���̂��q����̐l��
	int ninzuu = 0;
	//���q����������_���Ō��߂�
	int Rokyaku;
	//X�|�W�V����
	//float PosX = 0.0f;
	//���q����̔ԍ�
	int kyakunum = 0;
	//���������Ă��邨�q����
	int Nowscene = 0;
	//�􂢕��̐�
	int kirei = 0;
	//int karikirei = 0;
	//����p
	int kitanai = 0;
	//int kari = 0;
	float CL = 0.0f;

	int num = 1;

	int Kara = num;
	int Pote = num;
	int Yasai = num;
	int mizu = num;
	int kora = num;
	int otya = num;

	bool Yogore = true;

	int KanseiKekka = 0;	//�����������q����̐l��

	enum State
	{
		keisann,
		purasu,
		kaeru,
		kitanaine
	};
	State m_state = keisann;

	//CVector3 m_position = { -6400.0f,-15.0f,-20.0f };

	////�X�L�����f�������_���[
	//prefab::CSkinModelRender* m_hito = nullptr;
};

