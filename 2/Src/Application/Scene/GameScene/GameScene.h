#pragma once

#include"../BaseScene/BaseScene.h"

class EnemyBase;
class Player;
class TPSCamera;
class EnemySystem;
class GameSystem;

class GameScene : public BaseScene
{
public :

	GameScene()  { Init(); }
	~GameScene();

	void AddEnemyList(const std::shared_ptr<EnemyBase>& _target)
	{
		m_wpEnemyList.push_back(_target);
	}

	std::vector<std::weak_ptr<EnemyBase>> GetEnemyList() { return m_wpEnemyList; }

	std::shared_ptr<Player>			GetPlayer()			{ return m_spPlayer; }
	std::shared_ptr<TPSCamera>		GetTPSCamera()		{ return m_spTPSCamera; }
	std::shared_ptr<EnemySystem>	GetEnemySystem()	{ return m_spEnemySystem; }

	void Last();
private:

	void Event() override;
	void Init()  override;

	std::vector<std::weak_ptr<EnemyBase>> m_wpEnemyList;		//エネミー専用のリスト

	std::shared_ptr<Player>			m_spPlayer;
	std::shared_ptr<TPSCamera>		m_spTPSCamera;
	std::shared_ptr<EnemySystem>	m_spEnemySystem;
	std::shared_ptr<GameSystem>		m_spGameSystem;
	std::shared_ptr <KdAudioManager>	m_spAudio;			//効果音

	float m_time = 0.0f;

	bool	m_ClickFlg = false;
};
