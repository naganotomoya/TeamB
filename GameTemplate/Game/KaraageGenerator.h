#pragma once
class SceneKaraage;
class Player;
class Camera;
class KaraageGenerator : public IGameObject
{
public:
	KaraageGenerator();
	~KaraageGenerator();
	bool Start();
	//void TongMove();
	void KaraageMove(CVector3& pos, float dif);
	void KaraageSyori();
	void Update();

	//あげているからあげの時間を返す
	//初期は１５秒
	float ReturnKaraageJikan()
	{
		return KaraageS;
	}
	/*bool KaraageState()
	{
		return nextKara;
	}*/
	////完成したからあげの個数を返す。
	//int ReturnKaraageKansei()
	//{
	//	return KanseiKosuu;
	//}
	//void MinusKaraageKansei()
	//{
	//	KanseiKosuu--;
	//}

private:
	Player* m_player = nullptr;
	Camera* m_camera = nullptr;
	SceneKaraage* m_karaage = nullptr;
	//prefab::CSkinModelRender* m_tong = nullptr;		//スキンモデルレンダラー。
	prefab::CSkinModelRender* m_nama = nullptr;		//スキンモデルレンダラー。
	//prefab::CSkinModelRender* m_osara = nullptr;		//スキンモデルレンダラー。
	prefab::CSkinModelRender* m_kansei = nullptr;		//スキンモデルレンダラー。

	CVector3 ZeroScale = CVector3::Zero;			//全て０
	CVector3 m_StartPos = CVector3::Zero;			//初期のポジション。
	CVector3 m_Tongposition = CVector3::Zero;			//トングのポジション。
	CVector3 m_Kposition = CVector3::Zero;			//生からあげのポジション
	CVector3 m_Knseiposition = CVector3::Zero;			//完成からあげのポジション
	CVector3 m_KnseiStartposition = { 0.0f,-100.0f,-5.0f };			//完成からあげの初期ポジション
	//CVector3 m_Sposition = CVector3::Zero;			//お皿のポジション
	CVector3 m_Sposition = { -60.0f,0.0f,-10.0f };
	//CQuaternion m_Trotation = CQuaternion::Identity;	//トング回転。
	//CQuaternion m_Srotation = CQuaternion::Identity;	//お皿回転。
	//prefab::CSpriteRender* m_abura = nullptr;		//油の２D
	CQuaternion Hanten;								//回転
	//CVector3 m_aburaposition = CVector3::Zero;		//油のポジション
	CVector3 m_aburaposition = { -8.5f,0.0f,-2.5f };
	CVector3 KTdiff = CVector3::Zero;				//からあげとトングの距離
	CVector3 KSdiff = CVector3::Zero;				//からあげとお皿の距離
	CVector3 KAdiff = CVector3::Zero;				//からあげと油の距離

	prefab::CSpriteRender* waku = nullptr;
	prefab::CSpriteRender* baa = nullptr;
	CVector3 SScale = { 0.008f,0.008f,1.0f };
	//CVector3 baapos = CVector3::Zero;
	CVector3 baaScale = { 0.0f,0.008f,1.0f };
	CVector3 baapos = CVector3::Zero;
	CVector3 wakupos = CVector3::Zero;

	CVector4 baacolor = { 0.0f,0.5f,0.0f,1.0f };

	float KaraageS = 0;		//からあげをaげる秒数
	//int KanseiKosuu = 0;		//完成した個数
	int nowscene = 0;	//今のシーンこれがないといつでも動いちゃう
	float OverS = 20;		//からあげをaげる秒数
	//bool nextKara = false;

	enum State {
		StateIdle,
		Statepush,
		Statefry,
		Statekansei
	};
	State m_state = StateIdle;

	prefab::CSoundSource* m_age = nullptr;
};

