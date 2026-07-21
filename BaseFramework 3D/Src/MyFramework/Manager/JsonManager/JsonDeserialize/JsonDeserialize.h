#pragma once

class CreateObject;

class JsonDeserialize
{
public:
	JsonDeserialize()	= default;
	~JsonDeserialize() = default;

	void JsonToObject()const;

	void SetCreateObjectClass(std::shared_ptr<CreateObject> _inptr)
	{
		m_wpCreateObjectClass = _inptr;
	}

private:

	nlohmann::json	JsonDeserializeFunc(const std::string& _inpath)const;

	std::weak_ptr<CreateObject> m_wpCreateObjectClass;
};