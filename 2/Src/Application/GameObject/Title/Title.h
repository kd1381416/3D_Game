#pragma once

class Title :public KdGameObject
{
public:
	Title() {};
	~Title()override {};

	void Init()	override;
	void Update()	override;
	void DrawSprite()	override;

private:

	std::shared_ptr<KdTexture>	m_Tex;
	std::shared_ptr<KdTexture>	m_TitleTex;
	float	m_Alpha;
	float	m_AddAlpha;
};