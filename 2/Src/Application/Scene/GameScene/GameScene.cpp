#include "GameScene.h"
#include "../SceneManager.h"

#include <Application/GameObject/Camera/TPSCamera/TPSCamera.h>

#include <Application/GameObject/Ground/Ground.h>

#include <Application/GameObject/Player/Player.h>

#include <Application/GameObject/Enemy/Enemy1/Enemy1.h>

#include <Application/GameObject/Reticle/Reticle.h>

#include <Application/GameObject/SkyDoom/SkyDoom.h>

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

	//===敵1===
	for (int i = 0; i < 5; i++)
	{
		auto _enemy1 = std::make_shared<Enemy1>();
		_enemy1->Init();
		_enemy1->SetPos(Math::Vector3{ -20.0f +(10.0f * i),0.3f,15.0f });
		AddObject(_enemy1);
		AddEnemyList(_enemy1);
		_enemy1->SetTarget(m_spPlayer);
		_enemy1->SetCamera(m_spTPSCamera);
		_enemy1->SetOwner(this);
	}

	//===照準===
	auto _reticle = std::make_shared<Retricle>();
	_reticle->Init();
	AddObject(_reticle);

	//===背景===
	auto _skyDoom = std::make_shared<SkyDoom>();
	_skyDoom->Init();
	AddObject(_skyDoom);

	//===ターゲットをセット===
	m_spTPSCamera->SetTarget(m_spPlayer);

	//===参照するため紐づけ===
	m_spPlayer->SetCamera(m_spTPSCamera);
	_reticle->SetCamera(m_spTPSCamera);

	//===ゲームシーンをセット===
	m_spTPSCamera->SetOwner(this);

	/*ImGuiStyle& style = ImGui::GetStyle();

	style.WindowRounding = 8.0f;
	style.ChildRounding = 6.0f;
	style.FrameRounding = 5.0f;
	style.PopupRounding = 5.0f;
	style.GrabRounding = 5.0f;*/
}
