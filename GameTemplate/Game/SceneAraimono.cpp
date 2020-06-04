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
	DeleteGO(m_Yogore);
}

bool SceneAraimono::Start()
{
	m_camera = FindGO<Camera>("camera");
	m_player = FindGO<Player>("player");
	//���M
	m_osara = NewGO<prefab::CSkinModelRender>(1, "osara");
	m_osara->Init(L"modelData/KaraageS/sara.cmo");			//���M�̃��[�h
	m_Srotation.SetRotationDeg(CVector3::AxisX, 90.0f);		//90�x��]
	m_osara->SetRotation(m_Srotation);
	m_Oposition = { -5105.0f,-20.0f,-5.0f };					//�����ʒu
	m_osara->SetPosition(m_Oposition);

	//����
	m_Yogore = NewGO<prefab::CSpriteRender>(0);
	m_Yogore->Init(L"sprite/Phaikei/Dirt.dds", MainCamera().GetWidth(),
		MainCamera().GetHeight(),
		true);//����̃��[�h
	

	Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//���]
	m_Yogore->SetScale(Scale);
	m_Yogore->SetPosition(m_YogoPos);
	m_Yogore->SetRotation(Hanten);					//���]��K��

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
		//Osara();
	}

	//����Ŏ����ĉE��Ő􂤁B
	m_player->LosaraAnime();
	//����̎�̈ʒu
	m_player->SetLPosition({ -5110.0f,-23.0f,-10.0f });

	//�E��Ƃ��M�̋����𑪂�B
	ROdiff = m_player->ReturnRPlayerPosition() - m_Oposition;

	//�^�C�}�[�I����
	Araimo += GameTime().GetFrameDeltaTime();

	//����Œ�̉E��̃A�j���[�V�����ł��炤�H
	//�E��̂��M�̋�����30�ȉ���Pad��B�{�^���������ꂽ��ƃX�e�B�b�N
	if (ROdiff.Length() <= 20.0 && Pad(0).IsPress(enButtonB) && m_state != State_Generate) {
		//���M�����Ă����Ԃɕς���
		m_state = State_wash;
		
		//1�b�o�߂��邽�тɂ����������čŏI�����B
		if (Araimo >= 1.0f && Count != 3 ) {
			//����̃X�P�[����yogere_scale�Ɏ����Ă���
			CVector3 yogere_scale = m_Yogore->GetScale();
			yogere_scale.x /= 2;
			yogere_scale.y /= 2;

			m_Yogore->SetScale(yogere_scale);
			
			Araimo = 0.0f;
			Count++;
		}
			//�^�C�}�[��5�b�߂�����
		if (Count == 3 ) {
			DeleteGO(m_Yogore);						//���������
			m_osara->SetPosition(KPos);				//���M�𑼂̈ʒu�Ɉړ�������B
			KanseiSara++;				            //�����M�𑝂₷�B
			Araimo = 0.0f;							//�􂢕��̃^�C�}��0.0�ɂ���
			Count = 0;								//�k�����鐔�̏�����
			m_state = State_Generate;				//���M�𐶐�������
		}
	}

	if (m_state == State_Generate) {
		//���M���ړ�������
		if (Araimo >= 2.0) {						//2�b��������
			//���M�̃|�W�V�������ړ�
			m_osara->SetPosition(m_Oposition);
			//����𐶐�����
			m_Yogore = NewGO<prefab::CSpriteRender>(0);
			m_Yogore->Init(L"sprite/Phaikei/Dirt.dds", MainCamera().GetWidth(),
				MainCamera().GetHeight(),
				true);//����̃��[�h


			Hanten.SetRotationDeg(CVector3::AxisY, 180.0f);	//���]
			m_Yogore->SetScale(Scale);
			m_Yogore->SetPosition(m_YogoPos);
			m_Yogore->SetRotation(Hanten);					//���]��K��
			m_state = State_Nothing;				//�������Ă��Ȃ����
		}
	}
	

	/*m_state��State_wash�ɂ͂����Ă�
	�􂢏I�������ɂ��̕ӂł���������܂�State_wash�ɓ���*/
}