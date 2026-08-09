#include "KdGameObject.h"

#include<Src/Application/main.h>

#include<MyFramework/Manager/JsonManager/JsonManager.h>
#include <MyFramework/Manager/JsonManager/JsonUtility/JsonUtility.h>

void KdGameObject::DrawDebug()
{
	// 早期リターン
	if (!m_pDebugWire)return;

	m_pDebugWire->Draw();
}

void KdGameObject::SetScale(float scalar)
{
	Math::Vector3 scale(scalar);

	SetScale(scale);
}

void KdGameObject::SetScale(const Math::Vector3& scale)
{
	Math::Vector3 vecX = m_mWorld.Right();
	Math::Vector3 vecY = m_mWorld.Up();
	Math::Vector3 vecZ = m_mWorld.Backward(); 
	
	vecX.Normalize();
	vecY.Normalize();
	vecZ.Normalize();

	m_mWorld.Right(vecX * scale.x);
	m_mWorld.Up(vecY * scale.y);
	m_mWorld.Backward(vecZ * scale.z);
}

Math::Vector3 KdGameObject::GetScale() const
{
	return Math::Vector3(m_mWorld.Right().Length(), m_mWorld.Up().Length(), m_mWorld.Backward().Length());
}

void KdGameObject::CalcDistSqrFromCamera(const Math::Vector3& camPos)
{
	m_distSqrFromCamera = (m_mWorld.Translation() - camPos).LengthSquared();
}

bool KdGameObject::Intersects(const KdCollider::SphereInfo& targetShape, std::list<KdCollider::CollisionResult>* pResults)
{
	if (!m_pCollider) { return false; }

	return m_pCollider->Intersects(targetShape, m_mWorld, pResults);
}

bool KdGameObject::Intersects(const KdCollider::BoxInfo& targetBox, std::list<KdCollider::CollisionResult>* pResults)
{
	if (!m_pCollider) { return false; }

	return m_pCollider->Intersects(targetBox, m_mWorld, pResults);
}

bool KdGameObject::Intersects(const KdCollider::RayInfo& targetShape, std::list<KdCollider::CollisionResult>* pResults)
{
	if (!m_pCollider) { return false; }

	return m_pCollider->Intersects(targetShape, m_mWorld, pResults);
}

void KdGameObject::JsonInput(const nlohmann::json& _injson)
{
	const auto& _utility = Application::Instance().GetJsonManagerClass()->GetJsonUtirity();

	if (_injson.contains("Path"))	m_path		= _injson["Path"];
	if (_injson.contains("Pos"))	m_position	= _utility->JsonToVector3(_injson["Pos"]);
	if (_injson.contains("Scale"))	m_scale		= _utility->JsonToVector3(_injson["Scale"]);
	if (_injson.contains("Degree"))	m_degree	= _utility->JsonToVector3(_injson["Degree"]);
	if (_injson.contains("Color"))	m_color		= _utility->JsonToVector4(_injson["Color"]);
}

void KdGameObject::JsonSave(nlohmann::json & _injson)
{}
