#include "JsonDeserialize.h"

#include<Src/MyFramework/Manager/JsonManager/CreateObject/CreateObject.h>
#include<Src/MyFramework/Manager/JsonManager/JsonManager.h>

#include<Src/Application/Scene/SceneManager.h>
#include<Src/Application/Scene/BaseScene/BaseScene.h>

#include<Src/Application/main.h>

void JsonDeserialize::JsonToObject() const
{
	std::string	_name = SceneManager::Instance().GetCurrentScene()->GetSceneName();

	nlohmann::json _json = JsonDeserializeFunc("Json/" + _name);

	for (auto& it : _json)
	{
		if (const auto& sp = m_wpCreateObjectClass.lock())
		{
			if (!sp)return;

			sp->CreateObjectFunc(it["Name"], it);
		}
	}
}

nlohmann::json JsonDeserialize::JsonDeserializeFunc(const std::string& _inpath) const
{
	std::ifstream _input((_inpath + ".json").data());

	nlohmann::json _json;

	if (!_input.is_open())return _json;

	_input >> _json;

	_input.close();

	return _json;
}
