#pragma once

class RegisterObject
{
public:
	RegisterObject()	= default;
	~RegisterObject()	= default;
	
	//ファクトリーパターン
	template<typename T>
	void Register(const std::string& _inclassname)
	{
		auto _registerfunc = []()->std::shared_ptr<KdGameObject>
			{
				auto _object = std::make_shared<T>();
				_object->Init();
				return _object;
			};

		m_RegisterMap.emplace(_inclassname, _registerfunc);		//マップに登録
	}

	const auto& GetRegisterMap() const
	{
		return m_RegisterMap;
	}

private:

	std::unordered_map<std::string, std::function<std::shared_ptr<KdGameObject>()>>	m_RegisterMap;
};