#pragma once

class CreateObject;
class JsonDeserialize;
class JsonSerialize;
class JsonUtility;

class JsonManager
{
public:
	JsonManager()	= default;
	~JsonManager()	= default;

	void Init();

	std::shared_ptr<CreateObject>		GetCreateObject()		const	{ return m_CreateObjectClass; }
	std::shared_ptr<JsonDeserialize>	GetJsonDeserialize()	const	{ return m_JsonDeserializeClass; }
	std::shared_ptr<JsonSerialize>		GetJsonSerialize()		const	{ return m_JsonSerializeClass; }
	std::shared_ptr<JsonUtility>		GetJsonUtirity()		const	{ return m_JsonUtilityClass; }

private:

	std::shared_ptr<CreateObject>		m_CreateObjectClass;
	std::shared_ptr<JsonDeserialize>	m_JsonDeserializeClass;
	std::shared_ptr<JsonSerialize>		m_JsonSerializeClass;
	std::shared_ptr<JsonUtility>		m_JsonUtilityClass;
};