#pragma once
#include "../CameraBase.h"

class EnemyBase;
class GameScene;

class TPSCamera : public CameraBase
{
public:
	TPSCamera()							{}
	~TPSCamera()			override	{}

	void Init()				override;
	void PostUpdate()		override;
	
	void SetOwner(GameScene* _owner) { m_owner = _owner; }

	std::weak_ptr<EnemyBase> GetTargetEnemy() { return m_wpTargetEnemy; }

private:

	std::weak_ptr<EnemyBase>				m_wpTargetEnemy;	//ターゲットするエネミー

	GameScene* m_owner = nullptr;

	void SearchTargetEnemy();	//一番近いエネミーを探しターゲットにする
	void UpdateAimAssist();		//エイムアシスト

	float GetAngleDifferene(float _current, float _target);
};