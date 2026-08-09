#include "GameScene.h"
#include"../SceneManager.h"

#include"../../GameObject/Ground/Field/Field.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{
	// JsonToObject() によって生成済みのオブジェクトをリストから取得する
	for (const auto& obj : SceneManager::Instance().GetObjList())
	{
		if (!m_field)
		{
			if (auto _field = std::dynamic_pointer_cast<Field>(obj))
			{
				m_field = _field;
				continue;
			}
		}
	}

	//AddObject(m_field);
}
