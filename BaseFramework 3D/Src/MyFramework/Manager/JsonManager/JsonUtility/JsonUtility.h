#pragma once

class JsonUtility
{
public:
	JsonUtility()	= default;
	~JsonUtility() = default;

	nlohmann::json VectorToJson(const Math::Vector2& _inVector)const;
	nlohmann::json VectorToJson(const Math::Vector3& _inVector)const;
	nlohmann::json VectorToJson(const Math::Vector4& _inVector)const;
		
	Math::Vector2	JsonToVector2(const nlohmann::json& _injson)const;
	Math::Vector3	JsonToVector3(const nlohmann::json& _injson)const;
	Math::Vector4	JsonToVector4(const nlohmann::json& _injson)const;
};