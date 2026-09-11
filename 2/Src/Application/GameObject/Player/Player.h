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
	void GenerateDepthMapFromLight()	override;

	void SetCamera(const std::shared_ptr<TPSCamera>& _camera) { m_wpCamera = _camera; }

	PlayerState	GetNowState() { return m_nowState; }

private:

	void MovePlayer();

	std::shared_ptr	<KdModelWork>		m_spUpperModel;		//上半身モデル(通常)
	std::shared_ptr <KdModelWork>		m_spGatlingModel;	//上半身モデル(ガトリング)
	std::shared_ptr	<KdModelWork>		m_spUnderModel;		//下半身モデル	
	std::weak_ptr	<TPSCamera>			m_wpCamera;			//カメラ

	Math::Matrix	m_underMatrix = Math::Matrix::Identity;
	Math::Matrix	m_upperMatrix = Math::Matrix::Identity;

	Math::Vector3	m_scale = Math::Vector3::One;
	Math::Vector3	m_pos	= Math::Vector3::Zero;

	PlayerState		m_nowState = PlayerState::Nomal;
		
	float	m_movePower = 0.3f;		//移動速度
	float	m_angle		= 0.0f;		//向いている方向
	float	m_shotDilay = 0.0f;		//弾の発射間隔

	int		m_gatlingCount = 0;		//ガトリング時何発打ったかカウント

	bool	m_shotFlg = false;		//弾発射フラグ
};