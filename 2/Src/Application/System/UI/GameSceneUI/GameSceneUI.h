#pragma once

class GameSceneUI :public KdGameObject
{
public:

	GameSceneUI()				{};
	~GameSceneUI()	override	{};

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;

private:

	// 数字の切り取り位置(0～9)
	int m_numberRec[10] =
	{
		64 * 0,
		64 * 1,
		64 * 2,
		64 * 3,
		64 * 4,
		64 * 5,
		64 * 6,
		64 * 7,
		64 * 8,
		64 * 9
	};

};