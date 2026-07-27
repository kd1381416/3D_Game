#pragma once

class StageBase :public KdGameObject
{
public:
	StageBase()						{}
	virtual ~StageBase()	override	{}

	void Init()				override;
	void Update()			override;
	void DrawLit()			override;

private:

	std::shared_ptr<KdModelData>	m_spModel = nullptr;

};