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
	prefab::CSkinModelRender* m_osara = nullptr;//‚¨ŽM‚ÌƒXƒLƒ“ƒ‚ƒfƒ‹
	CVector3 m_Oposition = CVector3::Zero;			//‚¨ŽM‚Ìƒ|ƒWƒVƒ‡ƒ“
	CQuaternion m_Srotation = CQuaternion::Identity;//‚¨ŽM‚Ì‰ñ“]

};

