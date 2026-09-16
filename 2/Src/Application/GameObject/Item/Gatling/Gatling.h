#pragma once

class Player;

class Gatling :public KdGameObject
{
public:

	Gatling()			{};
	~Gatling()override	{};

	void Init()		override;
	void Update()	override;
	void DrawLit()	override;

private:

	//アイテムのモデル
	std::shared_ptr<KdModelData>	m_spModel;

	//プレイヤーの情報
	std::weak_ptr<Player>	m_wpPlayer;

	//座標
	Math::Vector3	m_pos;
};