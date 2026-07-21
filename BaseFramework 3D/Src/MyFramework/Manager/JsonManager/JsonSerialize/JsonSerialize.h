#pragma once

class JsonSerialize
{
public:
	JsonSerialize()		= default;
	~JsonSerialize()	= default;

	void JsonSerializeFunc(const nlohmann::json& _injson, const std::string _inpath)const;

	void AllSave();
};