#pragma once
class ProgressBar :public IGameObject
{
public:
	ProgressBar();
	~ProgressBar();
	bool Start();
	void Update();
	void PostRender(CRenderContext& rc);
private:
	prefab::CSpriteRender* k_spriteRender = nullptr;//���g���o�[
	prefab::CSpriteRender* p_spriteRender = nullptr;//�|�e�g�o�[
	prefab::CSpriteRender* waku = nullptr;//�g
	prefab::CSpriteRender* waku_01 = nullptr;//�g

	CVector3 k_position = {-580.0,300.0,0.0};//���g���o�[�̈ʒu
	CVector3 p_position = { -580.0,230.0,0.0 };//�|�e�g�o�[�̈ʒu
	CVector3 w_position = { -340.0,300.0,0.0 };//�g�̈ʒu
	CVector3 w01_position = { -340.0,230.0,0.0 };//�g�̈ʒu
	

	CVector3 effecto = { 15.0,50.0,0.0 };//���g���G�t�F�ʒu
	CVector3 effe = { 10.0,30.0,0.0 };//�|�e�g�G�t�F�ʒu

	float x = 1.0f;//�ԃo�[�����l
	float y = 1.0f;//���ʏ����l

	CFont m_font;
	int k = 0.0, p = 0.0;
};

