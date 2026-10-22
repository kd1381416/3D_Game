#include "ResultScene.h"
#include "../SceneManager.h"

#include <Application/GameObject/Result/Result.h>

ResultScene::~ResultScene()
{
	m_spAudio->Instance().StopAllSound();
}

void ResultScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void ResultScene::Init()
{
	std::shared_ptr<KdGameObject>	_Result;
	_Result = std::make_shared<Result>();
	_Result->Init();
	m_objList.push_back(_Result);
}
