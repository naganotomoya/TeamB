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
	//���̃V�[����Ԃ��B
	//0���炠��
	//1�|�e�g
	//2�h�����N
	//3�����
	//4�􂢕�
	//5��v
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
		Drink,		//2
		Morituke,	//3
		Araimono,	//4
		//Kaikei,		//5
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
	//prefab::CSpriteRender* m_spriteKaikei = nullptr;
	CQuaternion Hanten;
	prefab::CDirectionLight* lig = nullptr;
};