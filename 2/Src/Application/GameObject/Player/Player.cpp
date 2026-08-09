#include "Player.h"

void Player::Init()
{
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Model/Tank/Tank.gltf");

	m_pos = { 0.0f,1.0f,0.0f };
}

void Player::Update()
{
	Math::Vector3 _moveDirection = Math::Vector3::Zero;

	if (GetAsyncKeyState('W') & 0x8000) { _moveDirection += { 0.0f, 0.0f, 1.0f}; }
	if (GetAsyncKeyState('A') & 0x8000) { _moveDirection += {-1.0f, 0.0f, 0.0f}; }
	if (GetAsyncKeyState('S') & 0x8000) { _moveDirection += { 0.0f, 0.0f,-1.0f}; }
	if (GetAsyncKeyState('D') & 0x8000) { _moveDirection += { 1.0f, 0.0f, 0.0f}; }

	_moveDirection.Normalize();
	
	m_pos += (_moveDirection * m_movePower);
}

void Player::PostUpdate()
{
	Math::Matrix	_scale = Math::Matrix::CreateScale(m_scale);
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = _scale * _trans;
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
