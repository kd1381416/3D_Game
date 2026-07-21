#include "JsonSerialize.h"

#include<Src/Application/Scene/SceneManager.h>
#include<Src/Application/Scene/BaseScene/BaseScene.h>

void JsonSerialize::JsonSerializeFunc(const nlohmann::json& _injson, const std::string _inpath) const
{
	std::ofstream _output((_inpath + ".json").data());

	if (!_output.is_open())return;

	//Jsonにフォーマット(2スペース)
	_output << _injson.dump(2);

	_output.clear();
}

void JsonSerialize::AllSave()
{
	nlohmann::json _json = nlohmann::json::array();

	for (auto& it : SceneManager::Instance().GetObjList())
	{
		nlohmann::json _jsonobject;

		it->JsonSave(_jsonobject);

		_json.push_back(_jsonobject);
	}

	std::string _name = SceneManager::Instance().GetCurrentScene()->GetSceneName();

	JsonSerializeFunc(_json, "Json/" + _name);
}
