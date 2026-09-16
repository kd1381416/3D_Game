#include "Gatling.h"

#include <Application/Scene/SceneManager.h>

void Gatling::Init()
{
	m_spModel = std::make_shared<KdModelData>();

	m_pos = { 0,0,0 };
}

void Gatling::Update()
{
	KdCollider::SphereInfo	_sphere;
	_sphere.m_sphere.Center = m_pos;
	_sphere.m_sphere.Radius = 50.0f;
	_sphere.m_type = KdCollider::TypePlayer;

	//全てのオブジェクトと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(_sphere, nullptr))
		{
		}
	}

}

void Gatling::DrawLit()
{}
