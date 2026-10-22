#include "GameScene.h"
#include "../SceneManager.h"

#include <Application/GameObject/Camera/TPSCamera/TPSCamera.h>

#include <Application/GameObject/Ground/Ground.h>

#include <Application/GameObject/Player/Player.h>

#include <Application/GameObject/Enemy/Enemy1/Enemy1.h>
#include <Application/GameObject/Enemy/Boss/Boss.h>

#include <Application/GameObject/Reticle/Reticle.h>

#include <Application/GameObject/SkyDoom/SkyDoom.h>

#include <Application/GameObject/Portal/Portal.h>

#include <Application/System/EnemySystem/EnemySystem.h>
#include <Application/System/GameSystem/GameSystem.h>

GameScene::~GameScene()
{
	SceneManager::Instance().SetTime(m_spGameSystem->GetTime());
	SceneManager::Instance().SetPlayer(m_spPlayer->GetFlg());
}

void GameScene::Last()
{
	SceneManager::Instance().SetTime(m_spGameSystem->GetTime());
	SceneManager::Instance().SetPlayer(m_spPlayer->GetFlg());
}

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

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
	else
	{
		m_ClickFlg = false;
	}

	m_spEnemySystem->Update();
}

void GameScene::Init()
{
	//===カメラ===
	m_spTPSCamera = std::make_shared<TPSCamera>();
	m_spTPSCamera->Init();
	AddObject(m_spTPSCamera);

	//===地面===
	auto _ground = std::make_shared<Ground>();
	_ground->Init();
	AddObject(_ground);

	//===プレイヤー===
	m_spPlayer= std::make_shared<Player>();
	m_spPlayer->Init();
	AddObject(m_spPlayer);

	//===照準===
	auto _reticle = std::make_shared<Retricle>();
	_reticle->Init();
	AddObject(_reticle);

	//===背景===
	auto _skyDoom = std::make_shared<SkyDoom>();
	_skyDoom->Init();
	AddObject(_skyDoom);

	//===ポータル===
	auto _portal = std::make_shared<Portal>();
	_portal->Init();
	AddObject(_portal);	

	//===ターゲットをセット===
	m_spTPSCamera->SetTarget(m_spPlayer);

	//===参照するため紐づけ===
	m_spPlayer->SetCamera(m_spTPSCamera);
	_reticle->SetCamera(m_spTPSCamera);

	//===ゲームシーンをセット===
	m_spTPSCamera->SetOwner(this);

	//===敵のイベント処理===
	m_spEnemySystem = std::make_shared<EnemySystem>();
	m_spEnemySystem->Init();
	m_spEnemySystem->SetGameScene(this);
	m_spEnemySystem->SetPortalPos(_portal->GetPos());

	//===ゲームのシステム===
	m_spGameSystem = std::make_shared<GameSystem>();
	m_spGameSystem->Init();
	AddObject(m_spGameSystem);

	m_spAudio->Instance().Play("Asset/Sound/Game/MusMus-BGM-170.wav", true);
}
