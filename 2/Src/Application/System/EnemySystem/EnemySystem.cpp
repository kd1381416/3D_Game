#include "EnemySystem.h"

#include <Application/Scene/SceneManager.h>
#include <Application/Scene/GameScene/GameScene.h>

#include <Application/GameObject/Enemy/Enemy1/Enemy1.h>
#include <Application/GameObject/Enemy/Boss/Boss.h>

void EnemySystem::Init()
{
}

void EnemySystem::Update()
{
	if (m_enemyDeathCount >= 10)
	{
		if (!m_bossFlg)
		{
			AddBoss();
		}
	}

	if (GetAsyncKeyState('B') & 0x8000)
	{
		if (!m_bossFlg)
		{
			AddBoss();
		}
	}

	if (m_enemyNowNum < m_enemyMaxNum)
	{
		AddNormalEnemy(m_portalPos.x, m_portalPos.z);
	}
}

void EnemySystem::AddNormalEnemy(float _xPos, float _zPos)
{
	if (m_enemyNowNum >= m_enemyMaxNum)return;

	auto _normalEnemy = std::make_shared<Enemy1>();

	if(_normalEnemy)
	{
		_normalEnemy->Init();
		_normalEnemy->SetPos(Math::Vector3{ _xPos + KdRandom::GetFloat(-1.0f, 1.0f), -1.0f,_zPos + KdRandom::GetFloat(-1.0f, 1.0f) });

		m_pGameScene->AddObject(_normalEnemy);
		AddEnemyList(_normalEnemy);

		if (m_pGameScene)
		{
			_normalEnemy->SetTarget(m_pGameScene->GetPlayer());
			_normalEnemy->SetOwner(m_pGameScene);

			m_enemyNowNum++;
		}
	}
}

void EnemySystem::AddBoss()
{
	auto _boss = std::make_shared<Boss>();

	if (_boss)
	{
		_boss->Init();
		_boss->SetPos(Math::Vector3{ m_portalPos.x , -1.0f, m_portalPos.z });

		m_pGameScene->AddObject(_boss);
		AddEnemyList(_boss);

		if (m_pGameScene)
		{
			_boss->SetTarget(m_pGameScene->GetPlayer());
			_boss->SetOwner(m_pGameScene);
		}
	}

	m_bossFlg = true;
}
