#include "Result.h"

#include <Application/Scene/SceneManager.h>

void Result::Init()
{
	//m_spScoreTex = std::make_shared<KdTexture>();
	m_spClearTex = std::make_shared<KdTexture>();
	m_spLoseTex = std::make_shared<KdTexture>();
	m_spClickTex = std::make_shared<KdTexture>();
	//m_spScoreTex->Load("Asset/Textures/Result/Number.png");
	m_spClearTex->Load("Asset/Textures/Result/Clear.png");
	m_spLoseTex->Load("Asset/Textures/Result/Lose.png");
	m_spClickTex->Load("Asset/Textures/Result/ClickTitle.png");
	//m_time = SceneManager::Instance().GetTime();

	m_time = 0;

	m_Alpha = 1;
	m_AddAlpha = -0.01;

	if (SceneManager::Instance().GetPlayer())
	{
		m_spAudio->Instance().Play("Asset/Sound/Result/MusMus-BGM-104.wav", true);
	}
	else
	{
		m_spAudio->Instance().Play("Asset/Sound/Result/Lose.wav", false);
	}
}

void Result::Update()
{
	m_Alpha += m_AddAlpha;

	if (m_Alpha >= 1 || m_Alpha <= 0)
	{
		m_AddAlpha *= -1;
	}
}

void Result::DrawSprite()
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

	//for (int i = 0; i < MaxDigits; i++)
	//{
	//	Math::Rectangle numrec = { numberanime[m_Digits[i]], 0, 64,	64 };
	//	Math::Color color = { 1, 1, 1, 1 };

	//	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spScoreTex, -100 + i * 100, 0, 100, 100, &numrec, &color, Math::Vector2{ 1.0f, 1.0f });
	//}

	Math::Rectangle numrec = { 0, 0, 512,256 };
	Math::Color color = { 1, 1, 1, 1 };
	
	if(SceneManager::Instance().GetPlayer())
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spClearTex, 0, 0, 600, 500, &numrec, &color, Math::Vector2{ 0.5f, 0.5f });
	}
	else
	{
		KdShaderManager::Instance().m_spriteShader.DrawTex(m_spLoseTex, 0, 0, 600, 500, &numrec, &color, Math::Vector2{ 0.5f, 0.5f });
	}
	color = { 1, 1, 1, m_Alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_spClickTex, -10, -200, 300, 250, &numrec, &color, Math::Vector2{ 0.5f, 0.5f });

}