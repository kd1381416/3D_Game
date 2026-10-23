#pragma once

class TPSCamera;

class Player :public KdGameObject
{
public:

	Player()			{};
	~Player()override	{};

	enum class PlayerState
	{
		Nomal,
		Gatling
	};

	void Init()							override;
	void Update()						override;
	void PostUpdate()					override;
	void DrawLit()						override;
	void DrawSprite()					override;
	void GenerateDepthMapFromLight()	override;
	void OnHit()						override;

	void SetCamera(const std::shared_ptr<TPSCamera>& _camera) { m_wpCamera = _camera; }

	PlayerState	GetNowState() { return m_nowState; }
	bool		GetFlg() { return m_activeFlg; }

	void ChangeState(PlayerState _changeState) { m_nowState = _changeState; }

private:

	void MovePlayer();

	std::shared_ptr	<KdModelWork>		m_spUpperModel;		//上半身モデル(通常)
	std::shared_ptr <KdModelWork>		m_spGatlingModel;	//上半身モデル(ガトリング)
	std::shared_ptr	<KdModelWork>		m_spUnderModel;		//下半身モデル	
	std::shared_ptr <KdAudioManager>	m_spAudio;			//効果音
	std::shared_ptr	<KdTexture>			m_HpTex;			//Hpのテクスチャ
	std::shared_ptr	<KdTexture>			m_CannonTex;		//大砲の残弾数のテクスチャ
	std::shared_ptr	<KdTexture>			m_GatlingTex;		//ガトリングの残弾数のテクスチャ
	std::shared_ptr	<KdTexture>			m_NumberTex;		//数字のテクスチャ
	std::shared_ptr	<KdTexture>			m_BoxTex;			//枠組みのテクスチャ
	std::shared_ptr	<KdTexture>			m_WhiteTex;			//チャージのテクスチャ
	std::weak_ptr	<TPSCamera>			m_wpCamera;			//カメラ

	Math::Matrix	m_underMatrix = Math::Matrix::Identity;
	Math::Matrix	m_upperMatrix = Math::Matrix::Identity;

	Math::Vector3	m_scale = Math::Vector3::One;
	Math::Vector3	m_pos	= Math::Vector3::Zero;

	PlayerState		m_nowState = PlayerState::Nomal;
		
	float	m_movePower		= 0.3f;		//移動速度
	float	m_angle			= 0.0f;		//向いている方向
	float	m_shotDilay		= 0.0f;		//弾の発射間隔
	float	m_CannonDilay	= 60.0f;	//Cannonの発射間隔
	float	m_GatlingDilay	= 100.0f;	//Gatlingの発射間隔
	float	m_MaxHp			= 100;
	float	m_Hp			= m_MaxHp;
	float	m_HitInterval	= 0;

	int		m_gatlingCount	= 0;			//ガトリング時何発打ったかカウント
	int		m_gatlingMax	= 25;			//ガトリングMax弾数

	bool	m_shotFlg = false;			//弾発射フラグ
	bool	m_stateChangeFlg = false;	//状態変更フラグ
	bool	m_gatlingSoundFlg = false;
	bool	m_activeFlg = true;

	static const int	MaxDigits = 2;
	int					m_Digits[MaxDigits] = { 0,0 };
};