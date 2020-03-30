#pragma once
class Player;
class SceneAraimono : public IGameObject
{
public:
	SceneAraimono();
	~SceneAraimono();
	bool Start();
	void Update();
private:
	Player* m_player = nullptr;
	prefab::CSkinModelRender* m_osara = nullptr;//お皿のスキンモデル
	CVector3 m_Oposition = CVector3::Zero;			//お皿のポジション
	CQuaternion m_Srotation = CQuaternion::Identity;//お皿の回転

};

