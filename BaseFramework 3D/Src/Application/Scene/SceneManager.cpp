#include "SceneManager.h"

#include "BaseScene/BaseScene.h"
#include "TitleScene/TitleScene.h"
#include "GameScene/GameScene.h"

#include<Application/main.h>

#include<MyFramework/Manager/JsonManager/JsonManager.h>
#include<MyFramework/RegisterObject/RegisterObject.h>
#include<MyFramework/Manager/JsonManager/JsonDeserialize/JsonDeserialize.h>

#include<Application/GameObject/Ground/GroundBase.h>
#include<Application/GameObject/Ground/Field/Field.h>

void SceneManager::Init()
{
	Register();

	ChangeScene(m_currentSceneType);

	m_currentScene->Init();
}

void SceneManager::Register()
{
	auto _registerObjectClass = Application::Instance().GetRegisterObjectClass();

	if (!_registerObjectClass)return;

	//オブジェクト登録
	_registerObjectClass->Register<KdGameObject>("KdGameObject");
	_registerObjectClass->Register<GroundBase>	("GroundBase");

	_registerObjectClass->Register<Field>		("Field");
}

void SceneManager::PreUpdate()
{
	// シーン切替
	if (m_currentSceneType != m_nextSceneType)
	{
		ChangeScene(m_nextSceneType);
	}

	m_currentScene->PreUpdate();
}

void SceneManager::Update()
{
	m_currentScene->Update();
}

void SceneManager::PostUpdate()
{
	m_currentScene->PostUpdate();
}

void SceneManager::PreDraw()
{
	m_currentScene->PreDraw();
}

void SceneManager::Draw()
{
	m_currentScene->Draw();
}

void SceneManager::DrawSprite()
{
	m_currentScene->DrawSprite();
}

void SceneManager::DrawDebug()
{
	m_currentScene->DrawDebug();
}

const std::list<std::shared_ptr<KdGameObject>>& SceneManager::GetObjList()
{
	return m_currentScene->GetObjList();
}

void SceneManager::AddObject(const std::shared_ptr<KdGameObject>& _obj)
{
	m_currentScene->AddObject(_obj);
}

void SceneManager::ChangeScene(SceneType _sceneType)
{
	// 次のシーンを作成し、現在のシーンにする
	switch (_sceneType)
	{
	case SceneType::Title:
		m_currentScene = std::make_shared<TitleScene>();
		break;
	case SceneType::Game:
		m_currentScene = std::make_shared<GameScene>();
		break;
	}

	// 現在のシーン情報を更新
	m_currentSceneType = _sceneType;

	if (m_currentScene)
	{
		auto CreateObject = Application::Instance().GetJsonManagerClass()->GetJsonDeserialize();

		if (!CreateObject) return;

		CreateObject->JsonToObject();
	}
}
