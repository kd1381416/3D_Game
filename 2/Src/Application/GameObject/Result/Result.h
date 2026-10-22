#pragma once

class Result : public KdGameObject
{
public:
	Result() {};
	~Result()	override {};

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;
private:

	std::shared_ptr<KdTexture>	m_spScoreTex;
	std::shared_ptr<KdTexture>	m_spClearTex;
	std::shared_ptr<KdTexture>	m_spLoseTex;
	std::shared_ptr<KdTexture>	m_spClickTex;
	std::shared_ptr <KdAudioManager>	m_spAudio;			//効果音

	int m_time;

	static const int	MaxDigits = 4;
	int					m_Digits[MaxDigits] = { 0,0,0,0 };

	float	m_Alpha;
	float	m_AddAlpha;
};