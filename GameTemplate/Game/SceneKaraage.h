#pragma once
class Player;
class Camera;
class SceneKaraage : public IGameObject
{
public:
	SceneKaraage();
	~SceneKaraage();
	bool Start();
	void TongMove();
	void KaraageMove(CVector3& pos);
	void KaraageSyori();
	void FrySyori();
	void Update();

	//あげているからあげの時間を返す
	float ReturnKaraageJikan()
	{
		return KaraageS;
	}
	//完成したからあげの個数を返す。
	int ReturnKaraageKansei()
	{
		return KanseiKosuu;
	}

private:
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	prefab::CSkinModelRender* m_tong = nullptr;		//スキンモデルレンダラー。
	prefab::CSkinModelRender* m_nama = nullptr;		//スキンモデルレンダラー。
	prefab::CSkinModelRender* m_osara = nullptr;		//スキンモデルレンダラー。
	prefab::CSkinModelRender* m_kansei = nullptr;		//スキンモデルレンダラー。


	CVector3 m_StartPos = CVector3::Zero;			//初期のポジション。
	CVector3 m_Tposition = CVector3::Zero;			//トングのポジション。
	CVector3 m_Kposition = CVector3::Zero;			//生からあげのポジション
	CVector3 m_Knseiposition = CVector3::Zero;			//完成からあげのポジション
	CVector3 m_Sposition = CVector3::Zero;			//お皿のポジション
	CQuaternion m_Trotation = CQuaternion::Identity;	//トング回転。
	CQuaternion m_Srotation = CQuaternion::Identity;	//おさえあ回転。
	prefab::CSpriteRender* m_abura = nullptr;		//油の２D
	CQuaternion Hanten;								//回転
	CVector3 m_aburaposition = CVector3::Zero;		//油のポジション
	CVector3 KTdiff = CVector3::Zero;				//からあげとトングの距離
	CVector3 KSdiff = CVector3::Zero;				//からあげとお皿の距離
	CVector3 KAdiff = CVector3::Zero;				//からあげと油の距離

	float KaraageS = 0;		//からあげをaげる秒数
	bool pushkara = false;		//からあげを持ったか
	bool fry = false;			//からあげをあげているか
	bool kansei = false;		//完成したからあげがあるか

	int KanseiKosuu = 0;		//完成した個数
	int nowscene = 0;	//今のシーンこれがないといつでも動いちゃう


	//prefab::CFontRender* m_fontkansei = nullptr;
	//wchar_t text[256];
};


