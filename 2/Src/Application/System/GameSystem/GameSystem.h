#pragma once

class GameSystem :public KdGameObject
{
public:
	GameSystem() {};
	~GameSystem()	override {};

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;

	int GetTime() { return m_time; }

private:

	// 数字のテクスチャ
	std::shared_ptr<KdTexture> m_spNumber = nullptr;

	// 経過フレーム数
	int m_time = 0;

	// 表示する数字（MM:SS）
	static constexpr int MaxDigits = 4;
	int m_Digits[MaxDigits] = { 0, 0, 0, 0 };
};