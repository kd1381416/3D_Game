#pragma once

#include"../BaseScene/BaseScene.h"

class Field;

class GameScene : public BaseScene
{
public :

	GameScene()  {}
	~GameScene() {}

	std::string GetSceneName()const override { return"Game"; }

private:

	void Event() override;
	void Init()  override;

	std::shared_ptr<Field>	m_field = nullptr;
};
