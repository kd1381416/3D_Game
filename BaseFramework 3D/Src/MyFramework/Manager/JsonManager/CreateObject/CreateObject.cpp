#include "CreateObject.h"

#include<Application/main.h>
#include<MyFramework/RegisterObject/RegisterObject.h>
#include<Application/Scene/SceneManager.h>

std::shared_ptr<KdGameObject> CreateObject::CreateObjectFunc(const std::string& _inclassname, const nlohmann::json& _injson) const
{
	auto _registerobject = Application::Instance().GetRegisterObjectClass()->GetRegisterMap();

	auto _found = _registerobject.find(_inclassname);

	if (_found == _registerobject.end())return nullptr;

	//インスタンスの生成
	std::shared_ptr<KdGameObject> _object = _found->second();

	if (_injson.is_null())_object->JsonInput(_injson);

	//オブジェクトリストへの追加
	SceneManager::Instance().AddObject(_object);

	return _object;
}
