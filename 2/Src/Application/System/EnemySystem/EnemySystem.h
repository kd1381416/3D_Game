#pragma once

class EnemyBase;
class GameScene;

class EnemySystem
{
public:

	EnemySystem()	{};
	~EnemySystem()	{};

	void Init();
	void Update();

	//敵(通常)を作成する(x軸座標,z軸座標)
	void AddNormalEnemy(float _xPos = 0.0f, float _zPos = 0.0f);

	//敵を追加したらこれを呼ぶ
	void AddEnemyList(const std::shared_ptr<EnemyBase> _enemy)
	{
		m_wpEnemyList.push_back(_enemy);
	}
	
	void SetGameScene(GameScene* _pGameScene)
	{
		m_pGameScene = _pGameScene;
	}

	void SetPortalPos(const Math::Vector3 _portalPos)
	{
		m_portalPos = _portalPos;
	}

	//敵専用のリストを取得する
	std::vector<std::weak_ptr<EnemyBase>> GetEnemyList()
	{
		return m_wpEnemyList;
	}

private:

	std::vector<std::weak_ptr<EnemyBase>>	m_wpEnemyList;		//エネミー専用のリスト

	GameScene* m_pGameScene;

	Math::Vector3	m_portalPos = {};

	int	m_enemyMaxNum = 5;
	int m_enemyNowNum = 0;
};