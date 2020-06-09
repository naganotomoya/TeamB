#include "stdafx.h"
#include "SceneKaikei.h"
#include "SpriteGenerator.h"
#include "SceneKaraage.h"
#include "ScenePoteto.h"
#include "SceneMorituke.h"
#include "SceneDrink.h"
#include "SceneAraimono.h"

SceneKaikei::SceneKaikei()
{

}
SceneKaikei::~SceneKaikei()
{
	QueryGOs<SpriteGenerator>("spritegenerator",
		[](SpriteGenerator* Spritegenerator)->bool {
			DeleteGO(Spritegenerator);
			return true;
		});
}

bool SceneKaikei::Start()
{
	//���f�������[�h
	/*m_hito = NewGO<prefab::CSkinModelRender>(0, "hito1");
	m_hito->Init(L"modelData/hito1.cmo");
	m_hito->SetPosition(m_position);*/

	//Kaikei[kyaku1].Karaage = true;

	m_karaage = FindGO<SceneKaraage>("karaage");
	m_poteto = FindGO<ScenePoteto>("poteto");
	m_morituke = FindGO<SceneMorituke>("morituke");
	m_drink = FindGO<SceneDrink>("drink");
	m_araimono = FindGO<SceneAraimono>("araimono");

	return true;
}

void SceneKaikei::SetKyakuNum()
{
	kyakunum++;
}

void SceneKaikei::NextTyuumon()
{
	Nowscene++;
}

//void SceneKaikei::KanseiKo()
//{
//	int Kara = num;
//	int Pote = num;
//	int Yasai = num;
//	int mizu = num;
//	int kora = num;
//	int otya = num;
//}

void SceneKaikei::Update()
{
	timer += GameTime().GetFrameDeltaTime();
	//�^�C�}�[��20���A���q���񂪏��Ȃ��A���􂢕����o���Ă����
	if (timer >= 5.0f &&
		ninzuu <= 1 &&
		Yogore == true) {
		//�����_���ł��q����̎�ނ�����
		Rokyaku = rand() % 4;
		//gene�����
		m_spriteGene = NewGO<SpriteGenerator>(0, "spritegenerator");
		//�l���𑝂₷
		ninzuu++;
		//�^�C�}�[�̏�����
		timer = 0.0f;
	}
}