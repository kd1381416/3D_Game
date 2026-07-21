#include "JsonUtility.h"

nlohmann::json JsonUtility::VecterToJson(const Math::Vector2& _invecter) const
{
	return nlohmann::json
	{
		{"X",_invecter.x},
		{"Y",_invecter.y}
	};
}

nlohmann::json JsonUtility::VecterToJson(const Math::Vector3& _invecter) const
{
	return nlohmann::json
	{
		{"X",_invecter.x},
		{"Y",_invecter.y},
		{"Z",_invecter.z}
	};
}

nlohmann::json JsonUtility::VecterToJson(const Math::Vector4& _invecter) const
{
	return nlohmann::json
	{
		{"X",_invecter.x},
		{"Y",_invecter.y},
		{"Z",_invecter.z},
		{"W",_invecter.w},
	};
}

Math::Vector2 JsonUtility::JsonToVecter2(const nlohmann::json& _injson) const
{
	return Math::Vector2
	{
		_injson["X"],
		_injson["Y"]
	};
}

Math::Vector3 JsonUtility::JsonToVecter3(const nlohmann::json& _injson) const
{
	return Math::Vector3
	{
		_injson["X"],
		_injson["Y"],
		_injson["Z"]
	};
}

Math::Vector4 JsonUtility::JsonToVecter4(const nlohmann::json& _injson) const
{
	return Math::Vector4
	{
		_injson["X"],
		_injson["Y"],
		_injson["Z"],
		_injson["W"]
	};
}
