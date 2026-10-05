#pragma once

class Player;
class GameScene;

class EnemyBase:public KdGameObject
{
public:
	EnemyBase() {}
	virtual ~EnemyBase() override {}

	enum class MoveState
	{
		None,
		Move,
		Attack,
		Death
	};

	virtual void Init()			override;
	virtual void Update()		override;
	virtual void PostUpdate()	override;
	virtual void DrawLit()		override;

	//状態を変更する関数
	virtual void ChangeState(MoveState _nextState) { m_currentState = _nextState; }

	virtual Math::Vector3 GetAimPos() const { return m_aimPos; }

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }

	void SetTarget(std::shared_ptr<Player> _target) { m_wpTarget = _target; }

	void SetOwner(GameScene* _owner) { m_owner = _owner; }

	float GetHp() const { return m_hp; }

private:

protected:

	MoveState	m_currentState = MoveState::None;

	std::shared_ptr	<KdModelWork>		m_spModel		= nullptr;		//モデル
	std::shared_ptr	<KdAnimator>		m_spAnimator	= nullptr;		//モデルのアニメーション
	std::weak_ptr	<Player>			m_wpTarget;						//ターゲット(Player)

	Math::Vector3	m_pos		= Math::Vector3::Zero;	//座標
	Math::Vector3	m_dir		= Math::Vector3::Zero;	//方向
	Math::Vector3	m_aimPos	= Math::Vector3::Zero;	//エイムを合わせる座標
	Math::Vector3	m_scale		= Math::Vector3::One;	//拡縮

	Math::Matrix	m_rotation;		//回転行列

	float m_movePower = 0.1f;		//移動速度
	float m_hp = 100.0f;			//体力

	bool m_moveFlg = false;			//行動フラグ
	bool m_changeFlg = false;		//状態変更フラグ
	bool m_animetionFlg = false;	//アニメーションフラグ

	GameScene* m_owner = nullptr;	//親(ゲームシーン)
};