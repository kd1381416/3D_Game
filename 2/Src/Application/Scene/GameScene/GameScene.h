#pragma once

#include"../BaseScene/BaseScene.h"

class EnemyBase;
class Player;
class TPSCamera;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene() {}

	void AddEnemyList(const std::shared_ptr<EnemyBase>& _target)
	{
		m_wpEnemyList.push_back(_target);
	}

	std::vector<std::weak_ptr<EnemyBase>> GetEnemyList() { return m_wpEnemyList; }

private:

	void Event() override;
	void Init()  override;

	std::vector<std::weak_ptr<EnemyBase>> m_wpEnemyList;		//エネミー専用のリスト

	std::shared_ptr<Player>		m_spPlayer;
	std::shared_ptr<TPSCamera>	m_spTPSCamera;
};
