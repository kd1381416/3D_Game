#include "Reticle.h"

#include<Application/GameObject/Camera/TPSCamera/TPSCamera.h>
#include<Application/GameObject/Enemy/EnemyBase.h>

void Retricle::Init()
{
	if (!m_spReticleTexture)
	{
		m_spReticleTexture = std::make_shared<KdTexture>();
		m_spReticleTexture->Load("Asset/Textures/UI/Reticle/Reticle.png");
	}

	if (!m_spTargetPolygon)
	{
		m_spTargetPolygon = std::make_shared<KdSquarePolygon>();
		m_spTargetPolygon->SetMaterial("Asset/Textures/UI/Reticle/Target.png");
		m_spTargetPolygon->SetPivot(KdSquarePolygon::PivotType::Center_Middle);
	}
}

void Retricle::Update()
{
	//カメラを取得
	auto _spCamera = m_wpCamera.lock();

	if (!_spCamera)return;

	//ターゲットになっている敵を取得
	auto _spTargetEnemy = _spCamera->GetTargetEnemy().lock();
	
	//ターゲットなし
	if (!_spTargetEnemy)
	{
		m_isTargetEnemy = false;
		m_pos = Math::Vector3::Zero;
		return;
	}

	//ターゲットあり
	m_isTargetEnemy = true;
	
	//ターゲットの座標取得
	Math::Vector3 _targetPos = _spTargetEnemy->GetAimPos();

	//敵の少し上を狙うようにする
	//_targetPos.y += 1.0f;

	_spCamera->GetCamera()->ConvertWorldToScreenDetail(_targetPos, m_pos);
		
	//敵の距離に応じてサイズを変える
	//float _distans = (_targetPos - _spCamera->GetPos()).Length();

	Math::Matrix	_scale	= Math::Matrix::CreateScale(3.0f);
	Math::Matrix	_trans	= Math::Matrix::CreateTranslation(_targetPos);
	Math::Matrix	_ratY	= _spCamera->GetRotationMatrix();
	m_mWorld = _scale * _ratY *_trans;
}

void Retricle::DrawEffect()
{
	if (m_isTargetEnemy)
	{
		if (!m_spTargetPolygon) return;
		KdShaderManager::Instance().ChangeDepthStencilState(KdDepthStencilState::ZDisable);
		KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spTargetPolygon, m_mWorld);
		KdShaderManager::Instance().UndoDepthStencilState();
	}
}

void Retricle::DrawBright()
{
	//if (m_isTargetEnemy)
	//{
	//	if (!m_spTargetPolygon) return;
	//	KdShaderManager::Instance().ChangeDepthStencilState(KdDepthStencilState::ZDisable);
	//	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spTargetPolygon, m_mWorld);
	//	KdShaderManager::Instance().UndoDepthStencilState();
	//}
}

void Retricle::DrawSprite()
{
	if (!m_spReticleTexture) return;
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spReticleTexture, m_pos.x, m_pos.y, 64, 64);
}
