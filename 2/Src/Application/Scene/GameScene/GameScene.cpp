#include "GameScene.h"
#include"../SceneManager.h"

#include<Application/GameObject/Camera/FPSCamera/FPSCamera.h>

#include<Application/GameObject/Ground/Ground.h>

#include<Application/GameObject/Player/Player.h>

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
	auto _fpsCamera = std::make_shared<FPSCamera>();
	_fpsCamera->Init();
	AddObject(_fpsCamera);

	auto _ground = std::make_shared<Ground>();
	_ground->Init();
	AddObject(_ground);

	auto _player = std::make_shared<Player>();
	_player->Init();
	AddObject(_player);

	_fpsCamera->SetTarget(_player);
}
