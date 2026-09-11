#include "EnemySystem.h"

#include <Application/Scene/SceneManager.h>
#include <Application/Scene/GameScene/GameScene.h>

#include <Application/GameObject/Enemy/Enemy1/Enemy1.h>

void EnemySystem::Init()
{
}

void EnemySystem::Update()
{
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
		_normalEnemy->SetPos(Math::Vector3{ _xPos,0.3f,_zPos });

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