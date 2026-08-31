#pragma once

class Player;
class GameScene;

class EnemyBase:public KdGameObject
{
public:
	EnemyBase() {}
	virtual ~EnemyBase() override {}

	virtual void Init()			override;
	virtual void Update()		override;
	virtual void PostUpdate()	override;
	virtual void DrawLit()		override;

	virtual Math::Vector3 GetAimPos() const { return m_aimPos; }

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void SetTarget(std::shared_ptr<Player> _target) { m_wpTarget = _target; }

	void SetOwner(GameScene* _owner) { m_owner = _owner; }

private:

protected:

	std::shared_ptr	<KdModelWork>		m_spModel		= nullptr;
	std::shared_ptr	<KdAnimator>		m_spAnimator	= nullptr;
	std::weak_ptr	<Player>			m_wpTarget;

	Math::Vector3	m_pos		= Math::Vector3::Zero;
	Math::Vector3	m_dir		= Math::Vector3::Zero;
	Math::Vector3	m_aimPos	= Math::Vector3::Zero;
	Math::Vector3	m_scale		= Math::Vector3::One;

	Math::Matrix	m_rotation;

	float m_movePower = 0.1f;		//移動速度
	float m_hp = 100.0f;			//体力

	bool m_moveFlg = false;
	bool m_animetionFlg = false;

	GameScene* m_owner = nullptr;
};