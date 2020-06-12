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
	DeleteGO(m_spriteYogore);
	QueryGOs<SpriteGenerator>("spritegenerator",
		[](SpriteGenerator* Spritegenerator)->bool {
			DeleteGO(Spritegenerator);
			return true;
		});
}

bool SceneKaikei::Start()
{
	//モデルをロード
	/*m_hito = NewGO<prefab::CSkinModelRender>(0, "hito1");
	m_hito->Init(L"modelData/hito1.cmo");
	m_hito->SetPosition(m_position);*/

	//Kaikei[kyaku1].Karaage = true;

	m_karaage = FindGO<SceneKaraage>("karaage");
	m_poteto = FindGO<ScenePoteto>("poteto");
	m_morituke = FindGO<SceneMorituke>("morituke");
	m_drink = FindGO<SceneDrink>("drink");
	m_araimono = FindGO<SceneAraimono>("araimono");


	m_spriteYogore = NewGO<prefab::CSpriteRender>(0);
	m_spriteYogore->Init(
		L"sprite/Karaage/kurai.dds",
		MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		false
	);
	m_spriteYogore->SetMulColor({ 1.0f,1.0f,1.0f ,0.0f });

	return true;
}

void SceneKaikei::YogoreSyori()
{
	kirei = m_araimono->ReturnPoteto();
	Yogoretimer += GameTime().GetFrameDeltaTime();

	if (Yogoretimer >= 20.0f) {
		kitanai++;
		Yogoretimer = 0.0f;
	}
	if (kirei < kitanai) {
		Yogore = false;
		if (CL <= 0.8f) {
			CL += 0.0005f;
		}
		else {
			CL = 0.8f;
		}
		m_spriteYogore->SetMulColor({ 1.0f,1.0f,1.0f ,CL });
	}
	else {
		Yogore = true;
		CL = 0.0f;
		m_spriteYogore->SetMulColor({ 1.0f,1.0f,1.0f ,0.0f });
	}

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
	YogoreSyori();
	timer += GameTime().GetFrameDeltaTime();
	//タイマーが20かつ、お客さんが少ない、かつ洗い物が出来ていれば
	if (timer >= 5.0f &&
		ninzuu <= 1 &&
		Yogore == true) {
		//ランダムでお客さんの種類を決定
		Rokyaku = rand() % 4;
		//geneを作る
		m_spriteGene = NewGO<SpriteGenerator>(0, "spritegenerator");
		//人数を増やす
		ninzuu++;
		//タイマーの初期化
		timer = 0.0f;
	}
}