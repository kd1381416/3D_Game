#include "JsonManager.h"

#include<MyFramework/Manager/JsonManager/CreateObject/CreateObject.h>
#include<MyFramework/Manager/JsonManager/JsonDeserialize/JsonDeserialize.h>
#include<MyFramework/Manager/JsonManager/JsonSerialize/JsonSerialize.h>
#include<MyFramework/Manager/JsonManager/JsonUtility/JsonUtility.h>

void JsonManager::Init()
{
	m_CreateObjectClass		= std::make_shared<CreateObject>();
	m_JsonDeserializeClass	= std::make_shared<JsonDeserialize>();
	m_JsonSerializeClass	= std::make_shared<JsonSerialize>();
	m_JsonUtilityClass		= std::make_shared<JsonUtility>();

	m_JsonDeserializeClass->SetCreateObjectClass(m_CreateObjectClass);
}