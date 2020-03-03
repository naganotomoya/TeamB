#pragma once
class Camera;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void SetXPosition(float x);
	void Animation();
	void Move();
	void Update();
	void PlusXPosition(float x)
	{
		m_Rposition.x += x;
		m_Lposition.x += x;
	}

	//右手の位置を返す
	CVector3 ReturnRPlayerPosition()
	{
		return m_Lposition;
	}
	//動かない方を動かす
	void SetLPosition(CVector3 pos)
	{
		m_Lposition = pos;
	}
	//動かない方の位置を返す
	CVector3 ReturnLPlayerPosition()
	{
		return m_Rposition;
	}
	//左手のアニメーション
	void LgripAnimation()
	{
		m_Rhand->PlayAnimation(rhandAC_grip);
	}
	void LopenAnimation()
	{
		m_Rhand->PlayAnimation(rhandAC_open);
	}

private:
	Camera* m_camera = nullptr;
	enum RHandAC {
		rhandAC_open,
		rhandAC_grip,
		rhandAC_Num,	//アニメーションクリップの数。
	};
	enum LHandAC {
		lhandAC_open,
		lhandAC_grip,
		lhandAC_Num,	//アニメーションクリップの数。
	};
	CAnimationClip m_Rac[rhandAC_Num];	//アニメーションクリップ。
	CAnimationClip m_Lac[lhandAC_Num];	//アニメーションクリップ。
	prefab::CSkinModelRender* m_Rhand = nullptr;		//スキンモデルレンダラー。
	prefab::CSkinModelRender* m_Lhand = nullptr;		//スキンモデルレンダラー。
	CVector3 m_Rposition = { 20.0f,-60.0f,0.0f };
	CVector3 m_Lposition = { 0.0f,0.0f,0.0f };

	float movespeed = 1.0f;	//移動速度
	float CX = 1280.0f;	//移動する距離
	int scenenum = 0;	//シーンの数
	int nowscene = 0;		//今のシーン番号
	float tyuusin = 0.0f;
};
