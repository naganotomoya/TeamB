#include "stdafx.h"
#include "SceneAraimono.h"
#include "Player.h"
#include "Camera.h"
SceneAraimono::SceneAraimono()
{
}
SceneAraimono::~SceneAraimono()
{
	DeleteGO(m_osara);
}

bool SceneAraimono::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	//���M
	m_osara = NewGO<prefab::CSkinModelRender>(0, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");			//���M�̃��[�h
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);		//90�x��]
	m_osara->SetRotation(m_Srotation);
	m_Oposition = { -5110.0f,0.0f,-1.0f };					//�����ʒu
	m_osara->SetPosition(m_Oposition);

	//����
	m_Yogore = NewGO<prefab::CSpriteRender>(0);
	m_Yogore->Init(L"sprite/Phaikei/Dirt.dds",800.0f,800.0f);//����̃��[�h
	m_Yogore->SetPosition(m_YogoPos);						 //�������W
	return true;
}

void SceneAraimono::Osara()
{
	m_Oposition = m_player->ReturnLPlayerPosition();
	m_Oposition.x += 5.0f;
	m_Oposition.y += 9.0f;
	m_Oposition.z -= 0.5f;
	m_osara->SetPosition(m_Oposition);
}

void SceneAraimono::Update()
{
	Nowscene = m_camera->ReturnNowScene();
	if (Nowscene == 4) {
		Osara();
	}
	
	//����Ŏ����ĉE��Ő􂤁B
	m_player->LosaraAnime();
	m_player->SetLPosition({ -5110.0f,0.0f,-3.0f });

	//�E��Ƃ��M�̋����𑪂�B
	ROdiff = m_player->ReturnRPlayerPosition() - m_Oposition;

	//����Œ�̉E��̃A�j���[�V�����ł��炤�H
	//�E��̂��M�̋�����30�ȉ���Pad��B�{�^���������ꂽ��ƃX�e�B�b�N
	if ( ROdiff.Length()<=30.0 && Pad(0).IsPress(enButtonB)) {
		Araimo += GameTime().GetFrameDeltaTime();
		
	}
	/*if (Araimo % 2==0.0) {

	}*/
	//�^�C�}�[��5�b�߂�����
	if (Araimo >= 5.0) {
		m_osara->SetPosition(KPos);
		KanseiSara++;				//�����M�𑝂₷�B
		Araimo = 0.0f;
	}
	/*������̃J�E���g�𒴂����炨�M�ꖇ���􂦂��B
	���̂��M�������ʒu�ɗp�ӂ���B&& Pad(0).GetLStickYF()*/
}