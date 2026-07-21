#pragma once

class CreateObject
{
public:
	CreateObject()		= default;
	~CreateObject()	= default;

	std::shared_ptr<KdGameObject>	CreateObjectFunc(const std::string& _inclassname, const nlohmann::json& _injson)const;
};