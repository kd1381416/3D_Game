#pragma once

class JsonManager
{
public:

	JsonManager()	{};
	~JsonManager()	{};

	//jsonロード
	void JsonLoad(const std::string& _fileName, nlohmann::json& _json)
	{
		std::ifstream file("Json/" + _fileName + ".json");

		if (!file.is_open())
		{
			assert(0 && "Jsonファイルパスが間違っています");
			return;
		}

		//ifstreamから_jsonに情報を上書き
		file >> _json;

		file.close();
	}

	//jsonセーブ
	void JsonSave(const std::string& _filePath, const nlohmann::json& _json)
	{
		std::ofstream file("Json/" + _filePath + ".json");

		if (!file.is_open())
		{
			assert(0 && "Jsonファイルパスが間違っています");
			return;
		}

		//_jsonからofstream(ファイル)に情報を上書き
		//dump(情報の書式(インデント)指定)
		file << _json.dump(4);

		file.close();
	}

	static JsonManager& Instance()
	{
		static JsonManager	instance;
		return instance;
	}
};