#pragma once
class Camera : public IGameObject
{
public:
	Camera();
	~Camera();
	bool Start();
	void Update();
	int Scenenum()
	{
		return SceneNum;
	}
	int ReturnNowScene()
	{
		return NowScene;
	}

private:
	struct  Position
	{
		float TxPos;	//�^�[�Q�b�g�|�W�V����
		float PxPos;	//�J�����|�W�V����
		//int BottonRL;	//�ǂ���̃{�^���������ꂽ���E��1�E�E2
	};
	enum Scene
	{
		Karaage,	//0
		Poteto,		//1
		Drink,
		Morituke,
		Araimono,
		Kaikei,		//5
		SceneNum
	};

	Position scene[SceneNum];
	//���̃V�[���̔ԍ�
	int NowScene = 0;
	//�ړ����鋗��
	float CX = 1280.0f;

	prefab::CSpriteRender* m_spriteKaraage = nullptr;
	prefab::CSpriteRender* m_spritePoteto = nullptr;
	prefab::CSpriteRender* m_spriteDrink = nullptr;
	prefab::CSpriteRender* m_spriteMorituke = nullptr;
	prefab::CSpriteRender* m_spriteAraimono = nullptr;
	prefab::CSpriteRender* m_spriteKaikei = nullptr;
	CQuaternion Hanten;
	prefab::CDirectionLight* lig = nullptr;
};