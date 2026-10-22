#include "TitleScene.h"
#include "../SceneManager.h"

#include<Application/GameObject/Title/Title.h>

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_ClickFlg)
		{
			m_ClickFlg = true;
			SceneManager::Instance().SetNextScene
			(
				SceneManager::SceneType::Game
			);
		}
	}
	else { m_ClickFlg = false; }

	if (GetAsyncKeyState('R') & 0x8000)
	{
		if (!m_ClickFlg)
		{
			m_ClickFlg = true;
			SceneManager::Instance().SetNextScene
			(
				SceneManager::SceneType::Result
			);
		}
	}
}

void TitleScene::Init()
{
	std::shared_ptr<KdGameObject>	_title;
	_title = std::make_shared<Title>();
	_title->Init();
	m_objList.push_back(_title);

	m_spAudio->Instance().Play("Asset/Sound/Title/MusMus-BGM-169.wav", true);
}
