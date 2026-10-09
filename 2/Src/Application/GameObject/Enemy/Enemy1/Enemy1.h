#pragma once

#include "../EnemyBase.h"

class Enemy1 : public EnemyBase
{
public:
	Enemy1(){}
	~Enemy1() override{}

	void Init()						override;
	void PreUpdate()				override;
	void Update()					override;
	void PostUpdate()				override;
	void DrawLit()					override;
	void GenerateDepthMapFromLight()override;

	void ChangeState(MoveState _nextState)	override;

	Math::Vector3 GetAimPos()const override { return m_aimPos; }
	
	void OnHit()override;

private:

	void SearchPlayer();
	void Attack();
	void Move();
	void Death();

	float m_animetionSpeed = 1.0f;	//アニメーションの速度

	//===とびかかり攻撃用===
	bool m_attackStarted = false;	//ジャンプ中かどうか
	bool m_attackLanded = false;	//着地しているかどうか

	Math::Vector3 m_attackDir = Math::Vector3::Zero;	//攻撃の方向(攻撃開始時に確定)

	Math::Vector3 m_attackVelocity = Math::Vector3::Zero;	//ジャンプ中の速度

	float m_attackGroundY = 0.0f;	//ジャンプ開始時の地面の高さ

	//ジャンプの各種パラメータ
	float m_attackJumpSpeed = 0.25f;
	float m_attackMoveSpeed = 0.12f;
	float m_attackGravity	= 0.01f;
};
