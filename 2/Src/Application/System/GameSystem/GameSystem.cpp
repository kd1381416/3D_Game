#include "GameSystem.h"

void GameSystem::Init()
{
	m_spNumber = std::make_shared<KdTexture>();
	m_spNumber->Load("Asset/Textures/Result/Number.png");

	m_time = 0;
}

void GameSystem::Update()
{
	++m_time;
}

void GameSystem::DrawSprite()
{
	// フレーム数から経過秒数を求める
	int totalSeconds = m_time / 60;

	// 分と秒に分ける
	int minutes = totalSeconds / 60;
	int seconds = totalSeconds % 60;

	// MM:SS の各桁を求める
	m_Digits[0] = (minutes / 10) % 10;
	m_Digits[1] = minutes % 10;
	m_Digits[2] = seconds / 10;
	m_Digits[3] = seconds % 10;

	// 画像内の数字の横位置
	int numberanime[10] =
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

	for (int i = 0; i < MaxDigits; i++)
	{
		Math::Rectangle numrec = { numberanime[m_Digits[i]], 0, 64,	64 };
		Math::Color color = { 1, 1, 1, 1 };

		//KdShaderManager::Instance().m_spriteShader.DrawTex(m_spNumber, -50 + i * 50, 250, 50, 50, &numrec, &color, Math::Vector2{ 1.0f, 1.0f });
	}
}