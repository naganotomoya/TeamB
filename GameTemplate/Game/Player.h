#pragma once
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();

private:
	enum RHandAC {
		rhandAC_open,
		rhandAC_grip,
		rhandAC_Num,	//アニメーションクリップの数。
	};
	//enum LHandAC {
	//	lhandAC_open,
	//	lhandAC_grip,
	//	lhandAC_Num,	//アニメーションクリップの数。
	//};

	CAnimationClip m_Rac[rhandAC_Num];	//アニメーションクリップ。
	//CAnimationClip m_Lac[lhandAC_Num];	//アニメーションクリップ。

	prefab::CSkinModelRender* m_Rhand = nullptr;		//スキンモデルレンダラー。
	prefab::CSkinModelRender* m_Lhand = nullptr;		//スキンモデルレンダラー。

};

