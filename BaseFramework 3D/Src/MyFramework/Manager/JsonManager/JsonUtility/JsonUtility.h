#pragma once

class JsonUtility
{
public:
	JsonUtility()	= default;
	~JsonUtility() = default;

	nlohmann::json VecterToJson(const Math::Vector2& _invecter)const;
	nlohmann::json VecterToJson(const Math::Vector3& _invecter)const;
	nlohmann::json VecterToJson(const Math::Vector4& _invecter)const;
		
	Math::Vector2	JsonToVecter2(const nlohmann::json& _injson)const;
	Math::Vector3	JsonToVecter3(const nlohmann::json& _injson)const;
	Math::Vector4	JsonToVecter4(const nlohmann::json& _injson)const;
};