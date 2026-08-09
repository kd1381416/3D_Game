#include "JsonUtility.h"

nlohmann::json JsonUtility::VectorToJson(const Math::Vector2& _inVector) const
{
	return nlohmann::json
	{
		{"x",_inVector.x},
		{"y",_inVector.y}
	};
}

nlohmann::json JsonUtility::VectorToJson(const Math::Vector3& _inVector) const
{
	return nlohmann::json
	{
		{"x",_inVector.x},
		{"y",_inVector.y},
		{"z",_inVector.z}
	};
}

nlohmann::json JsonUtility::VectorToJson(const Math::Vector4& _inVector) const
{
	return nlohmann::json
	{
		{"x",_inVector.x},
		{"y",_inVector.y},
		{"z",_inVector.z},
		{"w",_inVector.w},
	};
}

Math::Vector2 JsonUtility::JsonToVector2(const nlohmann::json& _injson) const
{
	return Math::Vector2
	{
		_injson["x"],
		_injson["y"]
	};
}

Math::Vector3 JsonUtility::JsonToVector3(const nlohmann::json& _injson) const
{
	return Math::Vector3
	{
		_injson["x"],
		_injson["y"],
		_injson["z"]
	};
}

Math::Vector4 JsonUtility::JsonToVector4(const nlohmann::json& _injson) const
{
	return Math::Vector4
	{
		_injson["x"],
		_injson["y"],
		_injson["z"],
		_injson["w"]
	};
}
