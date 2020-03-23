#pragma once
class ScenePoteto : public IGameObject
{
public:
	ScenePoteto();
	~ScenePoteto();
	bool Start();
	void Update();
private:
	prefab::CSkinModelRender* m_Poteto = nullptr;		//スキンモデルレンダラー。
	prefab::CSkinModelRender* m_osara = nullptr;		//スキルモデルレンダラー。
	prefab::CSpriteRender* m_abura = nullptr;		//油の２D
	CQuaternion Hanten;								//回転
	CVector3 m_aburaposition = CVector3::Zero;		//油のポジション
	CVector3 m_Pposition = CVector3::Zero;			//生ポテのポジション
};

