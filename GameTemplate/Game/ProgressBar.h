#pragma once
class ProgressBar :public IGameObject
{
public:
	ProgressBar();
	~ProgressBar();
	bool Start();
	void Update();
private:
	prefab::CSpriteRender* k_spriteRender = nullptr;//���g���o�[
	prefab::CSpriteRender* p_spriteRender = nullptr;//�|�e�g�o�[

	CVector3 k_position = {-580.0,300.0,0.0};//���g���o�[�̈ʒu
	CVector3 p_position = { -580.0,250.0,0.0 };//�|�e�g�o�[�̈ʒu
	

	CVector3 effecto = { 30.0,160.0,0.0 };//���g���G�t�F�ʒu
	CVector3 effe = { 70.0,140.0,0.0 };//�|�e�g�G�t�F�ʒu

	float x = 1.0f;//�ԃo�[�����l
	float y = 1.0f;//���ʏ����l
};

