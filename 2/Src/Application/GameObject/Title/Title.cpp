#include "Title.h"

void Title::Init()
{
	m_Tex = std::make_shared<KdTexture>();
	m_Tex->Load("Asset/Textures/Title/Start.png");

	m_TitleTex = std::make_shared<KdTexture>();
	m_TitleTex->Load("Asset/Textures/Title/TitleName.png");

	m_Alpha = 1;
	m_AddAlpha = -0.01;
}

void Title::Update()
{
	m_Alpha += m_AddAlpha;

	if (m_Alpha >= 1 || m_Alpha <= 0)
	{
		m_AddAlpha *= -1;
	}
}

void Title::DrawSprite()
{
	Math::Rectangle rec = { 0,0,200,50 };
	Math::Color	color = { 1,1,1,m_Alpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_Tex, 50, -200, 500, 200, &rec, &color, Math::Vector2{ 0.5,0.5 });

	Math::Rectangle titlerec = { 0,0,512,256 };
	Math::Color	titlecolor = { 1,1,1,1 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_TitleTex, -25, 200, 500, 200, &titlerec, &titlecolor, Math::Vector2{ 0.5,0.5 });
}