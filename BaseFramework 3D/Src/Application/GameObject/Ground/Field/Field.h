#pragma once

#include"../GroundBase.h"

class Field :public GroundBase
{
public:

	Field() = default;
	~Field()override = default;

	void Init()		override;
	void Update()	override;
	void DrawLit()	override;

	void JsonInput(const nlohmann::json& _injson)override;

private:

};