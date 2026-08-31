#pragma once

#include "../EnemyBase.h"

class TPSCamera;

class Enemy1 : public EnemyBase
{
public:
	Enemy1(){}
	~Enemy1() override{}

	void Init() override;
	void Update() override;
	void PostUpdate() override;
	void DrawLit() override;
	void GenerateDepthMapFromLight()override;

	Math::Vector3	GetAimPos()const override { return m_aimPos; }

	void OnHit()override;
	
	void SetCamera(std::shared_ptr<TPSCamera> _camera) { m_wpCamera = _camera; }

private:

	std::weak_ptr<TPSCamera>	m_wpCamera;
};
