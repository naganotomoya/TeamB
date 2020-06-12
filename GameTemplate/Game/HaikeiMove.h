#pragma once
class HaikeiMove : public IGameObject
{
public:
	HaikeiMove();
	~HaikeiMove();
	bool Start();
	void Update();

private:

	prefab::CSpriteRender* m_haikei = nullptr;
	CVector3 HKpos = CVector3::Zero;
	CQuaternion Hanten;								//‰ñ“]
	bool yoko = false;
};



