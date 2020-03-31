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
	void Update();
	void PlusXPosition(float x)
	{
		m_Rposition.x += x;
		m_Lposition.x += x;
	}
	//Bを押している間手を閉じたい場合の処理
	//if (Pad(0).IsPress(enButtonB)) {
	//	player->RgripAnimation();
	//}
	//else {
	//	player->RopenAnimation();
	//}
	//右手のアニメーション(閉じる)
	void RgripAnimation()
	{
		m_Lhand->PlayAnimation(lhandAC_grip);
	}
	//右手のアニメーション(開く)
	void RopenAnimation()
	{
		m_Lhand->PlayAnimation(lhandAC_open);
	}
	//右手のz軸を設定する。
	void setRHandZ(float posz)
	{
		m_Lposition.z = posz;
	}
	//プレイヤーのY軸に引数分の回転を加える
	void PlayerKaiten(float yjiku)
	{
		Yjiku.SetRotationDeg(CVector3::AxisY, yjiku);
		m_Lhand->SetRotation(Yjiku);
	}


	//移動
	//キャラと一緒に移動させたいときに
	//引数にそのpositionを入れて使う。
	void Move(CVector3& pos);
	//右手の位置を返す
	CVector3 ReturnRPlayerPosition()
	{
		return m_Lposition;
	}
	//左手を動かす
	void SetLPosition(CVector3 pos)
	{
		m_Rposition = pos;
	}
	//左手位置を返す
	CVector3 ReturnLPlayerPosition()
	{
		return m_Rposition;
	}
	//左手お皿で使うアニメーション
	void LosaraAnime()
	{
		m_Rhand->PlayAnimation(rhandAC_osara);
	}
	void LosaraGrip()
	{
		m_Rhand->PlayAnimation(rhandAC_osaragrip);
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
		rhandAC_osara,
		rhandAC_osaragrip,
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
	CQuaternion Yjiku = CQuaternion::Identity;			//y軸周りの回転

	float movespeed = 1.0f;	//移動速度
	float CX = 1280.0f;	//移動する距離
	int scenenum = 0;	//シーンの数
	int nowscene = 0;		//今のシーン番号
	float tyuusin = 0.0f;
};